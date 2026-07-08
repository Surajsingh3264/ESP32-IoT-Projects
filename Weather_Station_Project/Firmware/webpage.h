#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>

// ==========================================
// PROGMEM HTML, CSS, JS ASSETS
// ==========================================
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Env Monitor</title>
    <style>
        :root {
            --bg: #f0f2f5;
            --card: #ffffff;
            --text-main: #1a1a1a;
            --text-sub: #65676b;
            --accent: #007bff;
            --border: #e4e6eb;
            --good: #28a745;
            --warn: #ffc107;
            --crit: #fd7e14;
            --emerg: #dc3545;
        }
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; }
        body { background-color: var(--bg); color: var(--text-main); padding: 15px; }
        header { display: flex; justify-content: space-between; align-items: center; max-width: 1200px; margin: 0 auto 20px auto; background: var(--card); padding: 15px 20px; border-radius: 12px; box-shadow: 0 2px 4px rgba(0,0,0,0.05); }
        .logo { display: flex; align-items: center; gap: 10px; font-weight: 700; font-size: 1.2rem; }
        .status-badge { display: flex; align-items: center; gap: 6px; font-size: 0.85rem; font-weight: 600; padding: 5px 10px; border-radius: 20px; background: #e8f5e9; color: var(--good); }
        .status-dot { width: 8px; height: 8px; background-color: var(--good); border-radius: 50%; }
        .offline .status-dot { background-color: var(--emerg); }
        .offline { background: #ffebee; color: var(--emerg); }
        .grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; max-width: 1200px; margin: 0 auto; }
        .card { background: var(--card); padding: 20px; border-radius: 12px; box-shadow: 0 2px 4px rgba(0,0,0,0.05); display: flex; flex-direction: column; justify-content: space-between; }
        .card-header { display: flex; justify-content: space-between; align-items: center; color: var(--text-sub); font-size: 0.9rem; font-weight: 600; margin-bottom: 10px; }
        .icon { width: 24px; height: 24px; fill: var(--accent); }
        .value { font-size: 1.8rem; font-weight: 700; color: var(--text-main); }
        .unit { font-size: 1rem; font-weight: 400; color: var(--text-sub); }
        .card-large { grid-column: span 2; text-align: center; padding: 30px 20px; }
        .card-large .value { font-size: 3rem; }
        .badge { display: inline-block; padding: 4px 12px; border-radius: 6px; font-size: 0.9rem; font-weight: 700; color: #fff; margin-top: 5px; text-transform: uppercase; }
        .footer-info { grid-column: span 2; display: flex; justify-content: space-around; background: var(--card); padding: 15px; border-radius: 12px; font-size: 0.85rem; color: var(--text-sub); box-shadow: 0 2px 4px rgba(0,0,0,0.05); }
        .btn-group { grid-column: span 2; display: flex; gap: 15px; }
        button { flex: 1; padding: 12px; border: none; background: var(--card); color: var(--accent); font-weight: 600; font-size: 0.9rem; border-radius: 12px; cursor: pointer; box-shadow: 0 2px 4px rgba(0,0,0,0.05); transition: background 0.2s; }
        button:hover { background: #e2e6ea; }
        .modal { display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: rgba(0,0,0,0.5); z-index: 100; justify-content: center; align-items: center; padding: 20px; }
        .modal-content { background: var(--card); padding: 25px; border-radius: 12px; max-width: 400px; width: 100%; box-shadow: 0 10px 20px rgba(0,0,0,0.2); }
        .modal-header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 15px; font-weight: 700; font-size: 1.1rem; }
        .close { cursor: pointer; font-size: 1.5rem; color: var(--text-sub); }
        .list-item { display: flex; justify-content: space-between; padding: 8px 0; border-bottom: 1px solid var(--border); font-size: 0.9rem; }
        .list-item:last-child { border-bottom: none; }
        .tag { padding: 2px 8px; border-radius: 4px; font-size: 0.75rem; font-weight: 700; }
        .tag-ok { background: #e8f5e9; color: var(--good); }
        .tag-err { background: #ffebee; color: var(--emerg); }
        @media (min-width: 768px) {
            .grid { grid-template-columns: repeat(4, 1fr); }
            .card-large { grid-column: span 2; }
            .footer-info, .btn-group { grid-column: span 4; }
        }
    </style>
</head>
<body>

<header>
    <div class="logo">
        <svg class="icon" viewBox="0 0 24 24"><path d="M12,2A10,10 0 0,0 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2M12,4A8,8 0 0,1 20,12A8,8 0 0,1 12,20A8,8 0 0,1 4,12A8,8 0 0,1 12,4M11,16.5L18,9.5L16.59,8.09L11,13.67L7.91,10.59L6.5,12L11,16.5Z"/></svg>
        Smart Env Monitor
    </div>
    <div id="connection-status" class="status-badge">
        <div class="status-dot"></div>
        <span id="conn-text">ONLINE</span>
    </div>
</header>

<div class="grid">
    <div class="card card-large">
        <div class="card-header">AIR QUALITY INDEX (AQI)</div>
        <div>
            <span id="val-aqi" class="value">--</span>
        </div>
        <div>
            <span id="badge-aqi" class="badge" style="background:var(--text-sub);">NO DATA</span>
        </div>
    </div>

    <div class="card card-large">
        <div class="card-header">SYSTEM & ALARM STATUS</div>
        <div style="margin: 10px 0;">
            <span style="font-size: 0.9rem; color: var(--text-sub);">System: </span>
            <span id="val-sys" style="font-weight:700; font-size:1.2rem;">--</span>
        </div>
        <div>
            <span style="font-size: 0.9rem; color: var(--text-sub);">Alarm: </span>
            <span id="val-alarm" style="font-weight:700; font-size:1.2rem;">--</span>
        </div>
    </div>

    <div class="card">
        <div class="card-header">
            <span>TEMPERATURE</span>
            <svg class="icon" viewBox="0 0 24 24"><path d="M15 13V5A3 3 0 0 0 9 5V13 A5 5 0 1 0 15 13M12 4A1 1 0 0 1 13 5V12.2L13.7 12.7A3 3 0 0 1 15 15A3 3 0 0 1 9 15A3 3 0 0 1 10.3 12.7L11 12.2V5A1 1 0 0 1 12 4Z"/></svg>
        </div>
        <div><span id="val-temp" class="value">--</span> <span class="unit">&deg;C</span></div>
    </div>

    <div class="card">
        <div class="card-header">
            <span>HUMIDITY</span>
            <svg class="icon" viewBox="0 0 24 24"><path d="M12,20A6,6 0 0,1 6,14C6,10 12,3.25 12,3.25C12,3.25 18,10 18,14A6,6 0 0,1 12,20Z"/></svg>
        </div>
        <div><span id="val-hum" class="value">--</span> <span class="unit">%</span></div>
    </div>

    <div class="card">
        <div class="card-header">
            <span>PRESSURE</span>
            <svg class="icon" viewBox="0 0 24 24"><path d="M12 2A10 10 0 0 0 2 12A10 10 0 0 0 12 22A10 10 0 0 0 22 12A10 10 0 0 0 12 2M12 4A8 8 0 0 1 20 12C20 14.4 19 16.5 17.5 18L16.1 16.6C17.3 15.3 18 13.7 18 12A6 6 0 0 0 12 6A6 6 0 0 0 6 12C6 13.7 6.7 15.3 7.9 16.6L6.5 18C5 16.5 4 14.4 4 12A8 8 0 0 1 12 4M12 9A3 3 0 0 0 9 12A3 3 0 0 0 12 15A3 3 0 0 0 15 12A3 3 0 0 0 12 9Z"/></svg>
        </div>
        <div><span id="val-pres" class="value">--</span> <span class="unit">hPa</span></div>
    </div>

    <div class="card">
        <div class="card-header">
            <span>LIGHT</span>
            <svg class="icon" viewBox="0 0 24 24"><path d="M12,18C11.11,18 10.26,17.8 9.5,17.45C11.56,16.5 13,14.42 13,12C13,9.58 11.56,7.5 9.5,6.55C10.26,6.2 11.11,6 12,6A6,6 0 0,1 18,12A6,6 0 0,1 12,18M20,8.69V4H15.31L12,0.69L8.69,4H4V8.69L0.69,12L4,15.31V20H8.69L12,23.31L15.31,20H20V15.31L23.31,12L20,8.69Z"/></svg>
        </div>
        <div><span id="val-light" class="value">--</span> <span class="unit">lx</span></div>
    </div>

    <div class="btn-group">
        <button onclick="openModal('mod-dev')">Device Info</button>
        <button onclick="openModal('mod-sens')">Sensor Status</button>
    </div>

    <div class="footer-info">
        <div>Connected Users: <strong id="val-clients">--</strong></div>
        <div>Last Updated: <strong id="val-time">Never</strong></div>
    </div>
</div>

<!-- Device Info Modal -->
<div id="mod-dev" class="modal">
    <div class="modal-content">
        <div class="modal-header">
            <span>Device Information</span>
            <span class="close" onclick="closeModal('mod-dev')">&times;</span>
        </div>
        <div class="list-item"><span>Board:</span><strong id="dev-board">--</strong></div>
        <div class="list-item"><span>Firmware:</span><strong id="dev-fw">--</strong></div>
        <div class="list-item"><span>IP Address:</span><strong id="dev-ip">--</strong></div>
        <div class="list-item"><span>WiFi SSID:</span><strong id="dev-ssid">--</strong></div>
        <div class="list-item"><span>Uptime:</span><strong id="dev-up">--</strong></div>
    </div>
</div>

<!-- Sensor Status Modal -->
<div id="mod-sens" class="modal">
    <div class="modal-content">
        <div class="modal-header">
            <span>Hardware Diagnostics</span>
            <span class="close" onclick="closeModal('mod-sens')">&times;</span>
        </div>
        <div class="list-item"><span>DHT22 (Temp/Hum):</span><span id="st-dht" class="tag">--</span></div>
        <div class="list-item"><span>BMP280 (Pressure):</span><span id="st-bmp" class="tag">--</span></div>
        <div class="list-item"><span>BH1750 (Light):</span><span id="st-bh" class="tag">--</span></div>
        <div class="list-item"><span>MQ135 (Air Quality):</span><span id="st-mq" class="tag">--</span></div>
    </div>
</div>

<script>
    function openModal(id) { document.getElementById(id).style.display = 'flex'; }
    function closeModal(id) { document.getElementById(id).style.display = 'none'; }
    window.onclick = function(e) { if (e.target.className === 'modal') e.target.style.display = 'none'; }

    function getBadgeColor(status) {
        if (status === 'GOOD') return 'var(--good)';
        if (status === 'MODERATE') return 'var(--warn)';
        if (status === 'POOR') return 'var(--crit)';
        if (status === 'HAZARDOUS') return 'var(--emerg)';
        return 'var(--text-sub)';
    }

    function setTag(elId, isOk) {
        let el = document.getElementById(elId);
        if (isOk) {
            el.textContent = "OK";
            el.className = "tag tag-ok";
        } else {
            el.textContent = "NOT FOUND";
            el.className = "tag tag-err";
        }
    }

    function fetchData() {
        let xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (this.readyState === 4) {
                let badge = document.getElementById('connection-status');
                let txt = document.getElementById('conn-text');
                
                if (this.status === 200) {
                    badge.classList.remove('offline');
                    txt.textContent = "ONLINE";
                    
                    let d = JSON.parse(this.responseText);
                    
                    document.getElementById('val-temp').textContent = d.temperature;
                    document.getElementById('val-hum').textContent = d.humidity;
                    document.getElementById('val-pres').textContent = d.pressure;
                    document.getElementById('val-light').textContent = d.light;
                    document.getElementById('val-aqi').textContent = d.aqi;
                    document.getElementById('val-sys').textContent = d.systemStatus;
                    document.getElementById('val-alarm').textContent = d.alarm;
                    document.getElementById('val-clients').textContent = d.clients;
                    document.getElementById('val-time').textContent = new Date().toLocaleTimeString();
                    
                    let bg = getBadgeColor(d.airStatus);
                    let aqiBadge = document.getElementById('badge-aqi');
                    aqiBadge.textContent = d.airStatus;
                    aqiBadge.style.background = bg;
                    document.getElementById('val-sys').style.color = bg;
                    
                    document.getElementById('dev-board').textContent = d.board;
                    document.getElementById('dev-fw').textContent = d.fw;
                    document.getElementById('dev-ip').textContent = d.ip;
                    document.getElementById('dev-ssid').textContent = d.ssid;
                    document.getElementById('dev-up').textContent = d.uptime;
                    
                    setTag('st-dht', d.dht);
                    setTag('st-bmp', d.bmp);
                    setTag('st-bh', d.bh1750);
                    setTag('st-mq', d.mq135);
                } else {
                    badge.classList.add('offline');
                    txt.textContent = "OFFLINE";
                }
            }
        };
        xhr.open("GET", "/data", true);
        xhr.timeout = 800;
        xhr.send();
    }

    setInterval(fetchData, 1000);
    fetchData();
</script>
</body>
</html>
)rawliteral";

#endif // WEBPAGE_H
