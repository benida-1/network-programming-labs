const dgram = require('dgram');
const WebSocket = require('ws');
const http = require('http');
const fs = require('fs');
const path = require('path');

const UDP_PORT = 5005;
const WS_PORT = 8080;

function purgeOldLogs() {
  const cutoff = Date.now() - (24 * 60 * 60 * 1000); // 24 hours
  const file = path.join(__dirname, 'temperature_log.csv');
  if (!fs.existsSync(file)) return;

  const lines = fs.readFileSync(file, 'utf-8').split('\n');
  const header = lines[0];
  const filtered = lines.filter(line => {
    const ts = line.split(',')[0];
    return line === header || (new Date(ts).getTime() > cutoff);
  });

  fs.writeFileSync(file, filtered.join('\n'));
}
setInterval(purgeOldLogs, 60 * 60 * 1000); // Run every 1 hour

const udpServer = dgram.createSocket('udp4');
const httpServer = http.createServer((req, res) => {
  if (req.url === '/download-csv') {
    const file = path.join(__dirname, 'temperature_log.csv');
    res.setHeader('Content-Disposition', 'attachment; filename="temperature_log.csv"');
    res.setHeader('Content-Type', 'text/csv');
    fs.createReadStream(file).pipe(res);
    return; // 🔥 prevent further processing
  }

  // Default: serve the HTML file
  const file = path.join(__dirname, 'frontend', 'index.html');
  fs.readFile(file, (err, data) => {
    if (err) {
      res.writeHead(500);
      res.end('Error loading HTML');
    } else {
      res.writeHead(200, { 'Content-Type': 'text/html' });
      res.end(data);
    }
  });
});


const wss = new WebSocket.Server({ server: httpServer });
let sockets = [];

// Create or append CSV file with headers
const csvPath = path.join(__dirname, 'temperature_log.csv');
if (!fs.existsSync(csvPath)) {
  fs.writeFileSync(csvPath, 'Timestamp,Sensor,Temperature,Unit\n');
}

wss.on('connection', (ws) => {
  sockets.push(ws);
  ws.on('close', () => {
    sockets = sockets.filter(s => s !== ws);
  });
});

udpServer.on('message', (msg) => {
  const message = msg.toString(); // e.g., "Sensor-1|25.7|°C"
  console.log('Received UDP:', message);

  // Send to frontend
  sockets.forEach(ws => ws.send(message));

  // Parse and log to CSV
  const [sensorId, temp, unit] = message.split('|');
  const timestamp = new Date().toISOString();
  if (sensorId && temp && unit) {
    const logLine = `${timestamp},${sensorId},${temp},${unit}\n`;
    fs.appendFile(csvPath, logLine, err => {
      if (err) console.error('CSV Logging Error:', err);
    });
  }
});

udpServer.bind(UDP_PORT);
httpServer.listen(WS_PORT, () => {
  console.log(`WebSocket + HTTP server running on port ${WS_PORT}`);
});


