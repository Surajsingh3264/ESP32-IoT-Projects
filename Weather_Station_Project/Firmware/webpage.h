#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>

// ==========================================
// PROGMEM HTML, CSS, JS ASSETS (LIGHT THEME + WATERMARKS)
// ==========================================
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Weather Station </title>
    <style>
        :root {
            --bg: #f1f5f9;
            --card-bg: #ffffff;
            --text-main: #0f172a;
            --text-sub: #64748b;
            --accent: #0284c7;
            --border: #e2e8f0;
            --good: #16a34a;
            --warn: #ca8a04;
            --crit: #ea580c;
            --emerg: #dc2626;
            --hero-grad: linear-gradient(135deg, #0284c7 0%, #2563eb 100%);
            --shadow: 0 4px 20px -2px rgba(148, 163, 184, 0.15);
            --shadow-hover: 0 12px 25px -4px rgba(148, 163, 184, 0.25);
        }
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; }
        body { background: var(--bg); color: var(--text-main); padding: 18px; min-height: 100vh; }
        
        /* Header */
        header { display: flex; justify-content: space-between; align-items: center; max-width: 1200px; margin: 0 auto 20px auto; background: var(--card-bg); padding: 16px 24px; border-radius: 18px; box-shadow: var(--shadow); border: 1px solid var(--border); }
        .logo { display: flex; align-items: center; gap: 12px; font-weight: 800; font-size: 1.35rem; color: var(--text-main); letter-spacing: -0.5px; }
        .logo-svg { width: 38px; height: 38px; }
        
        /* Status Badge */
        .status-badge { display: flex; align-items: center; gap: 8px; font-size: 0.85rem; font-weight: 700; padding: 6px 14px; border-radius: 30px; background: #dcfce7; color: var(--good); border: 1px solid #bbf7d0; transition: all 0.3s; }
        .status-dot { width: 8px; height: 8px; background-color: var(--good); border-radius: 50%; box-shadow: 0 0 8px var(--good); animation: pulse 2s infinite; }
        @keyframes pulse { 0%, 100% { opacity: 1; transform: scale(1); } 50% { opacity: 0.5; transform: scale(1.2); } }
        .offline { background: #fee2e2; color: var(--emerg); border-color: #fecaca; }
        .offline .status-dot { background-color: var(--emerg); box-shadow: 0 0 8px var(--emerg); animation: none; }
        
        /* Grid & Cards */
        .grid { display: grid; grid-template-columns: 1fr 1fr; gap: 18px; max-width: 1200px; margin: 0 auto; }
        .card { background: var(--card-bg); padding: 24px; border-radius: 22px; box-shadow: var(--shadow); border: 1px solid var(--border); display: flex; flex-direction: column; justify-content: space-between; position: relative; overflow: hidden; z-index: 1; transition: transform 0.25s ease, box-shadow 0.25s ease; }
        .card:hover { transform: translateY(-4px); box-shadow: var(--shadow-hover); }
        
        /* Background Watermark SVGs */
        .bg-watermark { position: absolute; right: -15px; bottom: -15px; width: 160px; height: 160px; opacity: 0.04; z-index: -1; pointer-events: none; transition: transform 0.4s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.4s; fill: var(--text-main); }
        .card:hover .bg-watermark { transform: scale(1.12) rotate(-6deg); opacity: 0.07; }
        
        /* Hero Card (Temperature) */
        .hero { grid-column: span 2; background: var(--hero-grad); border: none; padding: 30px; color: #ffffff; }
        .hero .card-header { color: rgba(255,255,255,0.9); }
        .hero .value { font-size: 4.5rem; color: #ffffff; text-shadow: 0 2px 10px rgba(0,0,0,0.15); }
        .hero .unit { font-size: 2rem; color: rgba(255,255,255,0.9); }
        .hero .bg-watermark { fill: #ffffff; opacity: 0.12; right: -5px; bottom: -10px; width: 220px; height: 220px; }
        .hero:hover .bg-watermark { opacity: 0.18; }
        
        /* Typography & Layout */
        .card-header { display: flex; justify-content: space-between; align-items: flex-start; color: var(--text-sub); font-size: 0.82rem; font-weight: 700; text-transform: uppercase; letter-spacing: 0.8px; margin-bottom: 14px; }
        .svg-icon { width: 40px; height: 40px; }
        
        .value-wrapper { margin: 10px 0; }
        .value { font-size: 2.4rem; font-weight: 800; color: var(--text-main); letter-spacing: -1px; }
        .unit { font-size: 1.1rem; font-weight: 600; color: var(--text-sub); }
        
        .sub-text { font-size: 0.92rem; font-weight: 700; color: var(--accent); margin-top: 6px; display: flex; align-items: center; gap: 6px; }
        .card-large { grid-column: span 2; }
        .row-item { display: flex; justify-content: space-between; align-items: center; padding: 12px 0; border-bottom: 1px solid #f1f5f9; }
        .row-item:last-child { border-bottom: none; }
        
        /* Buttons & Footer */
        .btn-group { grid-column: span 2; display: flex; gap: 16px; }
        button { flex: 1; padding: 15px; border: 1px solid var(--border); background: var(--card-bg); color: var(--text-main); font-weight: 700; font-size: 0.95rem; border-radius: 16px; cursor: pointer; transition: all 0.2s; display: flex; align-items: center; justify-content: center; gap: 8px; box-shadow: var(--shadow); }
        button:hover { background: #f8fafc; border-color: var(--accent); color: var(--accent); transform: translateY(-2px); }
        
        .footer-info { grid-column: span 2; display: flex; justify-content: space-around; background: var(--card-bg); padding: 18px; border-radius: 16px; font-size: 0.88rem; color: var(--text-sub); border: 1px solid var(--border); box-shadow: var(--shadow); }
        
        /* Modals */
        .modal { display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: rgba(15, 23, 42, 0.4); backdrop-filter: blur(4px); z-index: 100; justify-content: center; align-items: center; padding: 20px; }
        .modal-content { background: var(--card-bg); padding: 28px; border-radius: 22px; max-width: 420px; width: 100%; border: 1px solid var(--border); box-shadow: 0 20px 50px rgba(0,0,0,0.15); }
        .modal-header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 18px; font-weight: 800; font-size: 1.25rem; color: var(--text-main); }
        .close { cursor: pointer; font-size: 1.5rem; color: var(--text-sub); }
        .list-item { display: flex; justify-content: space-between; padding: 10px 0; border-bottom: 1px solid var(--border); font-size: 0.92rem; }
        .list-item:last-child { border-bottom: none; }
        .tag { padding: 4px 10px; border-radius: 6px; font-size: 0.75rem; font-weight: 800; }
        .tag-ok { background: #dcfce7; color: var(--good); }
        .tag-err { background: #fee2e2; color: var(--emerg); }
        
        @media (min-width: 768px) {
            .grid { grid-template-columns: repeat(4, 1fr); }
            .hero, .card-large { grid-column: span 2; }
            .footer-info, .btn-group { grid-column: span 4; }
        }
    </style>
</head>
<body>

<header>
    <div class="logo">
        <svg class="logo-svg" viewBox="0 0 64 64" fill="none"><circle cx="32" cy="32" r="28" fill="#e0f2fe"/><path d="M32 10V22M32 42V54M10 32H22M42 32H54M16.44 16.44L24.93 24.93M39.07 39.07L47.56 47.56M16.44 47.56L24.93 39.07M39.07 24.93L47.56 16.44" stroke="#0284c7" stroke-width="4" stroke-linecap="round"/><circle cx="32" cy="32" r="10" fill="#0284c7"/></svg>
        <span>Smart Weather <span style="color:var(--accent); font-weight:300;">Station</span></span>
    </div>
    <div id="connection-status" class="status-badge">
        <div class="status-dot"></div>
        <span id="conn-text">ONLINE</span>
    </div>
</header>

<div class="grid">
    <div class="card hero">
        <svg class="bg-watermark" viewBox="0 0 100 100"><path d="M10 50 Q 25 20, 50 50 T 90 50 M10 65 Q 25 35, 50 65 T 90 65 M10 35 Q 25 5, 50 35 T 90 35" fill="none" stroke="currentColor" stroke-width="6" stroke-linecap="round"/></svg>
        <div class="card-header">
            <span>AMBIENT TEMPERATURE</span>
            <svg class="svg-icon" viewBox="0 0 64 64" fill="none"><rect x="24" y="8" width="16" height="34" rx="8" fill="rgba(255,255,255,0.2)" stroke="#ffffff" stroke-width="3"/><circle cx="32" cy="46" r="12" fill="#ffffff"/><path d="M32 28V46" stroke="#ef4444" stroke-width="6" stroke-linecap="round"/><circle cx="32" cy="46" r="6" fill="#ef4444"/></svg>
        </div>
        <div class="value-wrapper">
            <span id="val-temp" class="value">--</span><span class="unit">&deg;C</span>
        </div>
        <div id="temp-desc" class="sub-text" style="color:#ffffff; opacity: 0.95;">Monitoring thermal comfort...</div>
    </div>

    <div class="card card-large">
        <svg class="bg-watermark" viewBox="0 0 100 100"><path d="M55 5 L25 55 H50 L45 95 L75 45 H50 Z" fill="currentColor"/></svg>
        <div class="card-header">
            <span>POWER & BATTERY STATUS</span>
            <svg class="svg-icon" id="bat-icon" viewBox="0 0 64 64" fill="none"><rect x="8" y="18" width="44" height="28" rx="6" fill="#f0f9ff" stroke="#0284c7" stroke-width="3"/><path d="M56 26H58C59.1046 26 60 26.8954 60 28V36C60 37.1046 59.1046 38 58 38H56V26Z" fill="#0284c7"/><rect id="bat-bar" x="13" y="23" width="34" height="18" rx="3" fill="#16a34a"/></svg>
        </div>
        <div class="row-item">
            <span style="color:var(--text-sub); font-weight:600;">Active Power Source:</span>
            <strong id="val-power" style="color:var(--accent); font-size:1.15rem;">--</strong>
        </div>
        <div class="row-item">
            <span style="color:var(--text-sub); font-weight:600;">Battery Level:</span>
            <div>
                <strong id="val-bat-pct" style="font-size:1.25rem;">--</strong>
                <span id="val-bat-volts" style="color:var(--text-sub); font-size:0.95rem; font-weight:600; margin-left:6px;">(-- V)</span>
            </div>
        </div>
    </div>

    <div class="card">
        <svg class="bg-watermark" viewBox="0 0 100 100"><path d="M50 10 C50 10 20 45 20 65 C20 82 33 95 50 95 C67 95 80 82 80 65 C80 45 50 10 50 10 Z" fill="currentColor"/></svg>
        <div class="card-header">
            <span>HUMIDITY</span>
            <svg class="svg-icon" viewBox="0 0 64 64" fill="none"><path d="M32 10C32 10 16 28 16 40C16 48.8366 23.1634 56 32 56C40.8366 56 48 48.8366 48 40C48 28 32 10 32 10Z" fill="#e0f2fe" stroke="#0284c7" stroke-width="3"/><path d="M38 38C40.2091 40.2091 40.2091 43.7909 38 46" stroke="#0284c7" stroke-width="3" stroke-linecap="round"/></svg>
        </div>
        <div class="value-wrapper"><span id="val-hum" class="value">--</span><span class="unit">%</span></div>
        <div class="sub-text" style="color:var(--text-sub);">Relative Moisture</div>
    </div>

    <div class="card">
        <svg class="bg-watermark" viewBox="0 0 100 100"><circle cx="50" cy="50" r="20" fill="currentColor"/><path d="M50 5V20M50 80V95M5 50H20M80 50H95M18 18L29 29M71 71L82 82M18 82L29 71M71 29L82 18" stroke="currentColor" stroke-width="8" stroke-linecap="round"/></svg>
        <div class="card-header">
            <span>LIGHT INTENSITY</span>
            <svg class="svg-icon" viewBox="0 0 64 64" fill="none"><circle cx="32" cy="32" r="14" fill="#fef9c3" stroke="#ca8a04" stroke-width="3"/><path d="M32 6V12M32 52V58M6 32H12M52 32H58M13.6 13.6L17.8 17.8M46.2 46.2L50.4 50.4M13.6 50.4L17.8 46.2M46.2 17.8L50.4 13.6" stroke="#ca8a04" stroke-width="3" stroke-linecap="round"/></svg>
        </div>
        <div class="value-wrapper"><span id="val-light" class="value">--</span><span class="unit">lx</span></div>
        <div id="val-light-type" class="sub-text" style="color:var(--warn); font-weight:800;">Evaluating...</div>
    </div>

    <div class="card card-large">
        <svg class="bg-watermark" viewBox="0 0 100 100"><path d="M10 30 H70 C80 30 85 20 75 10 C65 0 55 15 65 25 M10 60 H80 C90 60 95 70 85 80 C75 90 65 75 75 65 M10 85 H50" fill="none" stroke="currentColor" stroke-width="6" stroke-linecap="round"/></svg>
        <div class="card-header">
            <span>INDOOR AIR & SMOKE MONITOR (MQ135)</span>
            <svg class="svg-icon" viewBox="0 0 64 64" fill="none"><path d="M48 40H18C13.5817 40 10 36.4183 10 32C10 27.5817 13.5817 24 18 24C19.123 24 20.192 24.2312 21.1613 24.6483C22.686 20.2323 26.9691 17 32 17C38.0751 17 43 21.9249 43 28C43 28.3353 42.985 28.6672 42.9555 28.9951C47.4695 29.671 51 33.558 51 38.25C51 43.0825 47.0825 47 42.25 47H36" stroke="#64748b" stroke-width="3" stroke-linecap="round"/><path d="M24 48C24 48 26 53 30 53C34 53 34 47 38 47C42 47 42 53 42 53" stroke="#16a34a" stroke-width="3" stroke-linecap="round"/></svg>
        </div>
        <div class="row-item">
            <div>
                <span style="color:var(--text-sub); display:block; font-size:0.85rem; font-weight:600;">Gas / Smoke Status:</span>
                <strong id="val-smoke-status" style="font-size:1.45rem; color:var(--good);">--</strong>
            </div>
            <div style="text-align:right;">
                <span style="color:var(--text-sub); display:block; font-size:0.85rem; font-weight:600;">Raw Index Value:</span>
                <span id="val-gas-idx" style="font-weight:800; font-size:1.25rem;">--</span>
            </div>
        </div>
    </div>

    <div class="card card-large">
        <svg class="bg-watermark" viewBox="0 0 100 100"><circle cx="50" cy="50" r="40" fill="none" stroke="currentColor" stroke-width="6"/><path d="M50 50 L75 25 M30 70 L20 80 M70 70 L80 80" stroke="currentColor" stroke-width="6" stroke-linecap="round"/><circle cx="50" cy="50" r="8" fill="currentColor"/></svg>
        <div class="card-header">
            <span>BAROMETRIC PRESSURE & SYSTEM</span>
            <svg class="svg-icon" viewBox="0 0 64 64" fill="none"><circle cx="32" cy="32" r="22" fill="#e0f2fe" stroke="#0284c7" stroke-width="3"/><path d="M32 32L44 20" stroke="#dc2626" stroke-width="4" stroke-linecap="round"/><circle cx="32" cy="32" r="4" fill="#dc2626"/></svg>
        </div>
        <div class="row-item">
            <span style="color:var(--text-sub); font-weight:600;">Barometric Pressure:</span>
            <div><strong id="val-pres" style="font-size:1.25rem;">--</strong> <span class="unit">hPa</span></div>
        </div>
        <div class="row-item">
            <span style="color:var(--text-sub); font-weight:600;">System Alarm State:</span>
            <strong id="val-sys" style="font-size:1.15rem; color:var(--good);">--</strong>
        </div>
    </div>

    <div class="btn-group">
        <button onclick="openModal('mod-dev')"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><circle cx="12" cy="12" r="10"/><path d="M12 16v-4M12 8h.01"/></svg> Device Info</button>
        <button onclick="openModal('mod-sens')"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M22 12h-4l-3 9L9 3l-3 9H2"/></svg> Diagnostics</button>
    </div>

    <div class="footer-info">
        <div>Connected Clients: <strong id="val-clients" style="color:var(--text-main);">--</strong></div>
        <div>Last Sync: <strong id="val-time" style="color:var(--text-main);">Never</strong></div>
    </div>
</div>

<div id="mod-dev" class="modal"><div class="modal-content"><div class="modal-header"><span>Device Specs</span><span class="close" onclick="closeModal('mod-dev')">&times;</span></div><div class="list-item"><span>Board:</span><strong id="dev-board">--</strong></div><div class="list-item"><span>Firmware:</span><strong id="dev-fw">--</strong></div><div class="list-item"><span>IP Address:</span><strong id="dev-ip">--</strong></div><div class="list-item"><span>WiFi SSID:</span><strong id="dev-ssid">--</strong></div><div class="list-item"><span>Uptime:</span><strong id="dev-up">--</strong></div></div></div>
<div id="mod-sens" class="modal"><div class="modal-content"><div class="modal-header"><span>Hardware Buses</span><span class="close" onclick="closeModal('mod-sens')">&times;</span></div><div class="list-item"><span>DHT22 (Temp/Hum):</span><span id="st-dht" class="tag">--</span></div><div class="list-item"><span>BMP280 (Pressure):</span><span id="st-bmp" class="tag">--</span></div><div class="list-item"><span>BH1750 (Light):</span><span id="st-bh" class="tag">--</span></div><div class="list-item"><span>MQ135 (Gas/Smoke):</span><span id="st-mq" class="tag">--</span></div></div></div>

<script>
    function openModal(id) { document.getElementById(id).style.display = 'flex'; }
    function closeModal(id) { document.getElementById(id).style.display = 'none'; }
    window.onclick = function(e) { if (e.target.className === 'modal') e.target.style.display = 'none'; }
    function setTag(id, ok) { let el = document.getElementById(id); el.textContent = ok ? "OK" : "NOT FOUND"; el.className = ok ? "tag tag-ok" : "tag tag-err"; }

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
                    document.getElementById('val-light-type').textContent = d.lightType;
                    document.getElementById('val-gas-idx').textContent = d.gasIndex;
                    document.getElementById('val-smoke-status').textContent = d.smokeStatus;
                    document.getElementById('val-sys').textContent = d.systemStatus;
                    document.getElementById('val-clients').textContent = d.clients;
                    document.getElementById('val-time').textContent = new Date().toLocaleTimeString();
                    
                    // Power & Battery Styling
                    document.getElementById('val-power').textContent = d.powerSource;
                    if (d.batteryPct >= 0) {
                        document.getElementById('val-bat-pct').textContent = d.batteryPct + "%";
                        document.getElementById('val-bat-volts').textContent = "(" + d.batteryVolts + " V)";
                        document.getElementById('bat-bar').style.width = Math.max(5, (d.batteryPct / 100) * 34) + "px";
                        document.getElementById('bat-bar').setAttribute("fill", d.batteryPct > 20 ? "#16a34a" : "#dc2626");
                    } else {
                        document.getElementById('val-bat-pct').textContent = "No Battery";
                        document.getElementById('val-bat-volts').textContent = "(USB Power)";
                        document.getElementById('bat-bar').style.width = "34px";
                        document.getElementById('bat-bar').setAttribute("fill", "#0284c7");
                    }
                    
                    // Smoke status color
                    let smkEl = document.getElementById('val-smoke-status');
                    if (d.smokeStatus.includes("Clean")) smkEl.style.color = "var(--good)";
                    else if (d.smokeStatus.includes("Normal")) smkEl.style.color = "var(--warn)";
                    else smkEl.style.color = "var(--emerg)";

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
