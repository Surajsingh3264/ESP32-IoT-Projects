#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Weather Station</title>
    <style>
        :root {
            --bg: #f1f5f9;
            --card-bg: #ffffff;
            --text-main: #0f172a;
            --text-sub: #64748b;
            --border: #edf2f7;
            --shadow: 0 4px 18px -2px rgba(0, 0, 0, 0.05);
            --shadow-hover: 0 12px 25px -4px rgba(0, 0, 0, 0.1);
            --hero-grad: linear-gradient(135deg, #f97316 0%, #ea580c 100%);
        }
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif; }
        body { background: var(--bg); color: var(--text-main); padding: 20px; min-height: 100vh; overflow-x: hidden; }
        
        /* Navbar */
        header { display: flex; justify-content: space-between; align-items: center; max-width: 1100px; margin: 0 auto 20px auto; background: var(--card-bg); padding: 16px 24px; border-radius: 20px; box-shadow: var(--shadow); border: 1px solid var(--border); }
        .logo-area { display: flex; align-items: center; gap: 14px; }
        .logo-icon { width: 42px; height: 42px; }
        .logo-title { font-size: 1.3rem; font-weight: 800; color: var(--text-main); letter-spacing: -0.5px; }
        .logo-sub { font-size: 0.8rem; font-weight: 600; color: var(--text-sub); }
        .status-pill { display: flex; align-items: center; gap: 8px; font-size: 0.8rem; font-weight: 700; padding: 6px 14px; border-radius: 30px; background: #dcfce7; color: #16a34a; border: 1px solid #bbf7d0; }
        .status-dot-nav { width: 8px; height: 8px; background: #16a34a; border-radius: 50%; box-shadow: 0 0 8px #16a34a; animation: pulse 2s infinite; }
        @keyframes pulse { 0%, 100% { opacity: 1; } 50% { opacity: 0.4; } }
        .offline { background: #fee2e2; color: #dc2626; border-color: #fecaca; }
        .offline .status-dot-nav { background: #dc2626; box-shadow: none; animation: none; }

        /* Grid System */
        .grid { display: grid; grid-template-columns: repeat(6, 1fr); gap: 18px; max-width: 1100px; margin: 0 auto; }
        .card { padding: 24px; border-radius: 22px; box-shadow: var(--shadow); border: 1px solid var(--border); position: relative; overflow: hidden; transition: all 0.25s ease; display: flex; flex-direction: column; justify-content: space-between; }
        .card:hover { transform: translateY(-3px); box-shadow: var(--shadow-hover); }
        .span-6 { grid-column: span 6; } .span-3 { grid-column: span 3; } .span-2 { grid-column: span 2; }
        
        /* ======================================================== */
        /* 🎨 DYNAMIC PREMIUM COLOR THEMES                          */
        /* ======================================================== */
        .t-temp { background: var(--hero-grad); border: none; --c-main: #ffffff; --c-sub: rgba(255,255,255,0.85); --c-icn: #ffffff; --c-bg: rgba(255,255,255,0.2); --c-wm: #ffffff; }
        .t-bat  { background: linear-gradient(135deg, #f0fdf4, #dcfce7); border-color: #bbf7d0; --c-main: #14532d; --c-sub: #166534; --c-icn: #16a34a; --c-bg: #bbf7d0; --c-wm: #86efac; }
        .t-hum  { background: linear-gradient(135deg, #f0f9ff, #e0f2fe); border-color: #bae6fd; --c-main: #0c4a6e; --c-sub: #075985; --c-icn: #0284c7; --c-bg: #bae6fd; --c-wm: #7dd3fc; }
        .t-lgt  { background: linear-gradient(135deg, #fefce8, #fef08a); border-color: #fde047; --c-main: #713f12; --c-sub: #a16207; --c-icn: #ca8a04; --c-bg: #fde047; --c-wm: #facc15; }
        .t-prs  { background: linear-gradient(135deg, #faf5ff, #f3e8ff); border-color: #e9d5ff; --c-main: #581c87; --c-sub: #7e22ce; --c-icn: #9333ea; --c-bg: #e9d5ff; --c-wm: #d8b4fe; }
        .t-dew  { background: linear-gradient(135deg, #f0fdfa, #ccfbf1); border-color: #99f6e4; --c-main: #134e4a; --c-sub: #0f766e; --c-icn: #0d9488; --c-bg: #99f6e4; --c-wm: #5eead4; }
        .t-smk  { background: linear-gradient(135deg, #f8fafc, #f1f5f9); border-color: #e2e8f0; --c-main: #0f172a; --c-sub: #475569; --c-icn: #64748b; --c-bg: #e2e8f0; --c-wm: #cbd5e1; }
        
        /* Auto-Themed Elements */
        .header-title { color: var(--c-icn); display: flex; align-items: center; gap: 10px; font-size: 0.82rem; font-weight: 800; text-transform: uppercase; letter-spacing: 0.5px; }
        .icon-circle { background: var(--c-bg); color: var(--c-icn); width: 34px; height: 34px; border-radius: 50%; display: flex; align-items: center; justify-content: center; flex-shrink: 0; }
        .metric-val { color: var(--c-main); font-size: 2.4rem; font-weight: 800; letter-spacing: -1px; margin: 6px 0; }
        .metric-unit { color: var(--c-sub); font-size: 1.1rem; font-weight: 600; margin-left: 2px; }
        .sub-text { color: var(--c-sub); font-size: 0.85rem; font-weight: 600; margin-bottom: 8px;}
        
        /* Themed Badges */
        .badge { background: var(--c-bg); color: var(--c-main); font-size: 0.75rem; font-weight: 700; padding: 4px 12px; border-radius: 20px; display: flex; align-items: center; gap: 6px; width: fit-content; margin: 0 auto; }
        .badge .status-dot { background: var(--c-icn); width: 6px; height: 6px; border-radius: 50%; }

        /* Themed Background Watermark SVGs */
        .bg-watermark { position: absolute; right: -20px; bottom: -20px; width: 150px; height: 150px; color: var(--c-wm); opacity: 0.45; z-index: 0; pointer-events: none; transition: transform 0.4s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.4s; }
        .span-6 .bg-watermark { width: 220px; height: 220px; right: -10px; bottom: -30px; }
        .t-temp .bg-watermark { opacity: 0.15; }
        .card:hover .bg-watermark { transform: scale(1.15) rotate(-5deg); opacity: 0.7; }
        .card > div, .card > canvas, .card > .arch-wrap, .card > .aqi-bar-container { position: relative; z-index: 1; }
        .card-header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 12px; }

        /* Hero Card Overrides */
        .hero-body { display: flex; justify-content: space-between; align-items: center; flex-wrap: wrap; margin: 10px 0; }
        .temp-main { font-size: 4.5rem; font-weight: 800; color: var(--c-main); letter-spacing: -2px; line-height: 1; }
        .hero-chart-wrap { flex: 1; min-width: 180px; height: 80px; margin-left: 20px; }
        .stats-bar { display: flex; justify-content: space-around; background: rgba(255,255,255,0.15); padding: 14px; border-radius: 14px; border: 1px solid rgba(255,255,255,0.2); margin-top: 15px; flex-wrap: wrap; gap: 10px; }
        .stat-item { font-size: 0.88rem; font-weight: 700; color: var(--c-main); display: flex; align-items: center; gap: 6px; }

        /* Power & Battery Split Card */
        .split-card { display: flex; justify-content: space-between; align-items: center; flex-wrap: wrap; gap: 20px; }
        .split-half { flex: 1; min-width: 180px; display: flex; justify-content: space-between; align-items: center; padding: 10px; }
        .split-divider { width: 1px; height: 50px; background: var(--c-bg); }
        .power-label { font-size: 0.85rem; font-weight: 600; color: var(--c-sub); margin-bottom: 4px; }
        .power-val { font-size: 1.3rem; font-weight: 800; color: var(--c-main); }

        /* Sparklines & Charts */
        .sparkline-box { width: 100%; height: 50px; margin: 10px 0; }
        canvas { width: 100%; height: 100%; display: block; }
        .aqi-bar-container { width: 100%; margin: 15px 0 10px 0; }
        .aqi-bar { width: 100%; height: 10px; border-radius: 10px; background: linear-gradient(90deg, #22c55e 0%, #eab308 50%, #ef4444 100%); position: relative; box-shadow: inset 0 1px 3px rgba(0,0,0,0.1); }
        .aqi-thumb { width: 16px; height: 16px; background: #ffffff; border: 3px solid var(--c-main); border-radius: 50%; position: absolute; top: -3px; left: 0%; transition: left 0.5s ease; box-shadow: 0 2px 5px rgba(0,0,0,0.2); }
        
        /* Footer & Buttons */
        footer { max-width: 1100px; margin: 20px auto 0 auto; display: flex; justify-content: space-between; align-items: center; font-size: 0.85rem; font-weight: 600; color: var(--text-sub); padding: 10px 14px; flex-wrap: wrap; gap: 10px; }
        .btn-row { max-width: 1100px; margin: 15px auto 0 auto; display: flex; gap: 14px; }
        button { flex: 1; padding: 12px; border: 1px solid var(--border); background: var(--card-bg); color: var(--text-main); font-weight: 700; border-radius: 14px; cursor: pointer; box-shadow: var(--shadow); transition: all 0.2s; }
        button:hover { background: #f8fafc; color: #0284c7; border-color: #bae6fd; }
        
        /* Modals */
        .modal { display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: rgba(0,0,0,0.4); backdrop-filter: blur(4px); z-index: 100; justify-content: center; align-items: center; padding: 20px; }
        .modal-content { background: var(--card-bg); padding: 26px; border-radius: 22px; max-width: 400px; width: 100%; border: 1px solid var(--border); }
        .modal-header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 15px; font-weight: 800; font-size: 1.2rem; }
        .close { cursor: pointer; font-size: 1.5rem; color: var(--text-sub); }
        .list-item { display: flex; justify-content: space-between; padding: 10px 0; border-bottom: 1px solid var(--border); font-size: 0.9rem; }
        
        /* Mobile Override */
        @media (max-width: 850px) { 
            .grid { grid-template-columns: repeat(2, 1fr); gap: 12px; }
            .span-6, .card-mq { grid-column: span 2; }
            .span-2, .card-dew { grid-column: span 1; }
            .split-divider { display: none; }
            .temp-main { font-size: 3.2rem; } .metric-val { font-size: 1.7rem; } .metric-unit { font-size: 0.9rem; }
            .card { padding: 18px; } .header-title { font-size: 0.72rem; gap: 6px; }
            .icon-circle { width: 28px; height: 28px; } .icon-circle svg { width: 14px; height: 14px; }
            .stats-bar { padding: 10px; gap: 6px; } .stat-item { font-size: 0.78rem; }
            .hero-chart-wrap { margin-left: 0; margin-top: 10px; width: 100%; }
        }
    </style>
</head>
<body>

<header>
    <div class="logo-area">
        <svg class="logo-icon" viewBox="0 0 64 64"><circle cx="32" cy="32" r="26" fill="#ffedd5"/><path d="M46 38H22C16.4772 38 12 33.5228 12 28C12 22.4772 16.4772 18 22 18C23.3642 18 24.6644 18.2728 25.8453 18.7716C27.6974 13.4072 32.9038 9.5 39 9.5C46.4558 9.5 52.5 15.5442 52.5 23C52.5 23.407 52.4822 23.8099 52.4473 24.208C57.915 25.0294 62 29.7423 62 35.4C62 41.2542 57.2542 46 51.4 46H46" fill="#ffffff" stroke="#ea580c" stroke-width="3.5"/><circle cx="24" cy="20" r="6" fill="#facc15"/></svg>
        <div>
            <div class="logo-title">Smart Weather Station</div>
            <div class="logo-sub">Real-time Environmental Monitoring</div>
        </div>
    </div>
    <div id="connection-status" class="status-pill">
        <div class="status-dot-nav"></div>
        <span id="conn-text">ONLINE</span>
    </div>
</header>

<div class="grid">
    <div class="card span-6 t-temp">
        <svg class="bg-watermark" style="fill:currentColor;" viewBox="0 0 100 100"><path d="M50 15 A 10 10 0 0 0 40 25 V 60 A 20 20 0 1 0 60 60 V 25 A 10 10 0 0 0 50 15 Z M50 85 A 10 10 0 1 1 50 65 V 25 A 5 5 0 0 1 50 15 A 5 5 0 0 1 50 25 V 65 A 10 10 0 0 1 50 85 Z"/></svg>
        <div class="card-header">
            <div class="header-title">
                <div class="icon-circle"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M14 14.76V3.5a2.5 2.5 0 0 0-5 0v11.26a4.5 4.5 0 1 0 5 0z"/></svg></div>
                AMBIENT TEMPERATURE
            </div>
            <div class="badge" style="background:rgba(255,255,255,0.2);"><div class="status-dot"></div><span id="status-temp">Normal</span></div>
        </div>
        <div class="hero-body">
            <div><span id="val-temp" class="temp-main">--</span><span class="metric-unit"> &deg;C</span></div>
            <div class="hero-chart-wrap"><canvas id="chart-temp" width="400" height="80"></canvas></div>
        </div>
        <div class="sub-text" style="color:var(--c-main); opacity:0.9;">Monitoring thermal comfort...</div>
        <div class="stats-bar">
            <div class="stat-item"><span style="color:#fef08a;">&#128200;</span> Feels Like <span id="val-feels">-- &deg;C</span></div>
            <div class="stat-item"><span style="color:#bae6fd;">&#10052;</span> Min <span id="val-min">-- &deg;C</span></div>
            <div class="stat-item"><span style="color:#fecaca;">&#128293;</span> Max <span id="val-max">-- &deg;C</span></div>
        </div>
    </div>

    <div class="card span-6 t-bat">
        <svg class="bg-watermark" style="fill:currentColor;" viewBox="0 0 100 100"><path d="M55 5 L25 55 H50 L45 95 L75 45 H50 Z"/></svg>
        <div class="card-header"><div class="header-title"><div class="icon-circle"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M18 8h1a4 4 0 0 1 0 8h-1M2 8h16v9a4 4 0 0 1-4 4H6a4 4 0 0 1-4-4V8z"/><line x1="6" y1="1" x2="6" y2="4"/><line x1="10" y1="1" x2="10" y2="4"/><line x1="14" y1="1" x2="14" y2="4"/></svg></div>POWER & BATTERY STATUS</div></div>
        <div class="split-card">
            <div class="split-half">
                <div>
                    <div class="power-label">Active Power Source</div>
                    <div id="val-power" class="power-val">--</div>
                    <div id="val-power-sub" class="sub-text" style="margin:0; font-size:0.8rem;">(Checking...)</div>
                </div>
                <div class="icon-circle" style="width:48px; height:48px;"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M18 8h1a4 4 0 0 1 0 8h-1M2 8h16v9a4 4 0 0 1-4 4H6a4 4 0 0 1-4-4V8z"/></svg></div>
            </div>
            <div class="split-divider"></div>
            <div class="split-half">
                <div>
                    <div class="power-label">Battery Level</div>
                    <div id="val-bat-pct" class="power-val">--</div>
                    <div id="val-bat-volts" class="sub-text" style="margin:0; font-size:0.8rem;">(-- V)</div>
                </div>
                <div class="icon-circle" style="width:48px; height:48px; background:transparent; border:3px solid var(--c-icn);"><svg width="22" height="22" viewBox="0 0 24 24" fill="currentColor"><path d="M13 2L3 14h9l-1 8 10-12h-9l1-8z"/></svg></div>
            </div>
        </div>
    </div>

    <div class="card span-2 t-hum">
        <svg class="bg-watermark" style="fill:currentColor;" viewBox="0 0 100 100"><path d="M50 10 C50 10 20 45 20 65 C20 82 33 95 50 95 C67 95 80 82 80 65 C80 45 50 10 50 10 Z"/></svg>
        <div class="card-header"><div class="header-title"><div class="icon-circle"><svg width="18" height="18" viewBox="0 0 24 24" fill="currentColor"><path d="M12 2.69l5.66 5.66a8 8 0 1 1-11.31 0z"/></svg></div>HUMIDITY</div></div>
        <div><span id="val-hum" class="metric-val">--</span><span class="metric-unit"> %</span></div>
        <div class="sub-text">Relative Moisture</div>
        <div style="position:relative; width:100%; display:flex; justify-content:center; margin: 18px 0 8px 0;">
            <svg viewBox="0 0 100 55" style="width:100%; max-width:160px; height:auto;">
                <path d="M 15 50 A 35 35 0 0 1 85 50" fill="none" stroke="rgba(0,0,0,0.08)" stroke-width="8" stroke-linecap="round"/>
                <path id="arch-val" d="M 15 50 A 35 35 0 0 1 85 50" fill="none" stroke="var(--c-icn)" stroke-width="8" stroke-linecap="round" stroke-dasharray="109.95" stroke-dashoffset="109.95" style="transition: stroke-dashoffset 0.8s ease-in-out;"/>
            </svg>
            <svg style="position:absolute; bottom:5px; width:22px; height:22px; color:var(--c-icn);" viewBox="0 0 24 24" fill="currentColor"><path d="M12 2.69l5.66 5.66a8 8 0 1 1-11.31 0z"/></svg>
        </div>
        <div class="badge"><div class="status-dot"></div><span id="status-hum">Comfortable</span></div>
    </div>

    <div class="card span-2 t-lgt">
        <svg class="bg-watermark" style="fill:none; stroke:currentColor;" viewBox="0 0 100 100"><circle cx="50" cy="50" r="20" stroke-width="6"/><path d="M50 5V20M50 80V95M5 50H20M80 50H95M18 18L29 29M71 71L82 82M18 82L29 71M71 29L82 18" stroke-width="8" stroke-linecap="round"/></svg>
        <div class="card-header"><div class="header-title"><div class="icon-circle"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><circle cx="12" cy="12" r="5"/><path d="M12 1v2M12 21v2M4.22 4.22l1.42 1.42M18.36 18.36l1.42 1.42M1 12h2M21 12h2M4.22 19.78l1.42-1.42M18.36 5.64l1.42-1.42"/></svg></div>LIGHT INTENSITY</div></div>
        <div><span id="val-light" class="metric-val">--</span><span class="metric-unit"> lx</span></div>
        <div class="sub-text">Illuminance</div>
        <div class="sparkline-box"><canvas id="chart-light" width="200" height="50"></canvas></div>
        <div class="badge"><div class="status-dot"></div><span id="status-light">Bright</span></div>
    </div>

    <div class="card span-2 t-prs">
        <svg class="bg-watermark" style="fill:none; stroke:currentColor;" viewBox="0 0 100 100"><circle cx="50" cy="50" r="40" stroke-width="6"/><path d="M50 50 L75 25 M30 70 L20 80 M70 70 L80 80" stroke-width="6" stroke-linecap="round"/><circle cx="50" cy="50" r="8" fill="currentColor"/></svg>
        <div class="card-header"><div class="header-title"><div class="icon-circle"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><circle cx="12" cy="12" r="10"/><path d="M12 6v6l4 2"/></svg></div>PRESSURE</div></div>
        <div><span id="val-pres" class="metric-val">--</span><span class="metric-unit"> hPa</span></div>
        <div class="sub-text">Atmospheric Pressure</div>
        <div class="sparkline-box"><canvas id="chart-pres" width="200" height="50"></canvas></div>
        <div class="badge"><div class="status-dot"></div><span id="status-pres">Normal</span></div>
    </div>

    <div class="card span-3 card-dew t-dew">
        <svg class="bg-watermark" style="fill:none; stroke:currentColor;" viewBox="0 0 100 100"><path d="M30 65 A 20 20 0 0 1 40 30 A 25 25 0 0 1 80 45 A 15 15 0 0 1 80 75 H 30 Z" stroke-width="6" stroke-linecap="round"/></svg>
        <div class="card-header"><div class="header-title"><div class="icon-circle"><svg width="18" height="18" viewBox="0 0 24 24" fill="currentColor"><path d="M12 2.69l5.66 5.66a8 8 0 1 1-11.31 0z"/></svg></div>DEW POINT & SYSTEM</div></div>
        <div><span id="val-dew" class="metric-val">--</span><span class="metric-unit"> &deg;C</span></div>
        <div class="sub-text">Condensation Threshold</div>
        <div class="sparkline-box"><canvas id="chart-dew" width="200" height="50"></canvas></div>
        <div class="badge"><div class="status-dot"></div><span id="status-sys">System Normal</span></div>
    </div>

    <div class="card span-3 card-mq t-smk">
        <svg class="bg-watermark" style="fill:none; stroke:currentColor;" viewBox="0 0 100 100"><path d="M10 30 H70 C80 30 85 20 75 10 C65 0 55 15 65 25 M10 60 H80 C90 60 95 70 85 80 C75 90 65 75 75 65 M10 85 H50" stroke-width="6" stroke-linecap="round"/></svg>
        <div class="card-header"><div class="header-title"><div class="icon-circle"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M18 8h1a4 4 0 0 1 0 8h-1M2 8h16v9a4 4 0 0 1-4 4H6a4 4 0 0 1-4-4V8z"/></svg></div>INDOOR AIR & SMOKE (MQ135)</div></div>
        <div><span id="val-gas-idx" class="metric-val">--</span><span class="metric-unit"> Index</span></div>
        <div class="sub-text">Raw MOS Resistance Ratio</div>
        <div class="aqi-bar-container">
            <div class="aqi-bar"><div id="aqi-thumb" class="aqi-thumb"></div></div>
        </div>
        <div class="badge"><div class="status-dot"></div><span id="status-smoke">Clean Air (No Smoke)</span></div>
    </div>
</div>

<div class="btn-row">
    <button onclick="openModal('mod-dev')">&#128187; Device Specs</button>
    <button onclick="openModal('mod-sens')">&#128269; Hardware Diagnostics</button>
</div>

<footer>
    <div>&#128338; Last Updated: <span id="val-time">Never</span></div>
    <div>&#128260; Auto Refresh ON (1s) | Connected Clients: <strong id="val-clients" style="color:var(--text-main);">--</strong></div>
</footer>

<div id="mod-dev" class="modal"><div class="modal-content"><div class="modal-header"><span>Device Specs</span><span class="close" onclick="closeModal('mod-dev')">&times;</span></div><div class="list-item"><span>Board:</span><strong id="dev-board">--</strong></div><div class="list-item"><span>Firmware:</span><strong id="dev-fw">--</strong></div><div class="list-item"><span>mDNS Host:</span><strong>http://weather.local</strong></div><div class="list-item"><span>IP Address:</span><strong id="dev-ip">--</strong></div><div class="list-item"><span>Uptime:</span><strong id="dev-up">--</strong></div></div></div>
<div id="mod-sens" class="modal"><div class="modal-content"><div class="modal-header"><span>Hardware Buses</span><span class="close" onclick="closeModal('mod-sens')">&times;</span></div><div class="list-item"><span>DHT22 (Temp/Hum):</span><span id="st-dht">--</span></div><div class="list-item"><span>BMP280 (Pressure):</span><span id="st-bmp">--</span></div><div class="list-item"><span>BH1750 (Light):</span><span id="st-bh">--</span></div><div class="list-item"><span>MQ135 (Smoke):</span><span id="st-mq">--</span></div></div></div>

<script>
    function openModal(id) { document.getElementById(id).style.display = 'flex'; }
    function closeModal(id) { document.getElementById(id).style.display = 'none'; }
    window.onclick = function(e) { if (e.target.className === 'modal') e.target.style.display = 'none'; }

    let histTemp = [], histLight = [], histPres = [], histDew = [];
    let minTemp = Infinity, maxTemp = -Infinity;
    const MAX_PTS = 25;

    function drawSmoothSparkline(id, data, color, gradTop) {
        let canvas = document.getElementById(id); if (!canvas) return;
        let ctx = canvas.getContext('2d'); let w = canvas.width; let h = canvas.height;
        ctx.clearRect(0, 0, w, h); if (data.length < 2) return;
        let min = Math.min(...data), max = Math.max(...data);
        if (min === max) { min -= 1; max += 1; }
        let step = w / (data.length - 1);
        let pts = data.map((val, i) => ({ x: i * step, y: h - ((val - min) / (max - min)) * (h - 14) - 7 }));
        
        ctx.beginPath(); ctx.moveTo(pts[0].x, pts[0].y);
        for (let i = 0; i < pts.length - 1; i++) {
            let x_mid = (pts[i].x + pts[i+1].x) / 2, y_mid = (pts[i].y + pts[i+1].y) / 2;
            ctx.quadraticCurveTo(pts[i].x, pts[i].y, x_mid, y_mid);
        }
        ctx.lineTo(pts[pts.length-1].x, pts[pts.length-1].y);
        ctx.strokeStyle = color; ctx.lineWidth = 3; ctx.stroke();
        
        ctx.lineTo(pts[pts.length-1].x, h); ctx.lineTo(0, h); ctx.closePath();
        let grad = ctx.createLinearGradient(0, 0, 0, h);
        grad.addColorStop(0, gradTop); grad.addColorStop(1, 'rgba(255,255,255,0)');
        ctx.fillStyle = grad; ctx.fill();
    }

    function fetchData() {
        let xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (this.readyState === 4) {
                let badge = document.getElementById('connection-status');
                let txt = document.getElementById('conn-text');
                if (this.status === 200) {
                    badge.classList.remove('offline'); txt.textContent = "ONLINE";
                    let d = JSON.parse(this.responseText);
                    
                    let t = parseFloat(d.temperature); let h = parseFloat(d.humidity);
                    document.getElementById('val-temp').textContent = d.temperature;
                    document.getElementById('val-hum').textContent = d.humidity;
                    document.getElementById('val-pres').textContent = d.pressure;
                    document.getElementById('val-light').textContent = d.light;
                    document.getElementById('val-gas-idx').textContent = d.gasIndex;
                    document.getElementById('val-clients').textContent = d.clients;
                    document.getElementById('val-time').textContent = new Date().toLocaleTimeString();
                    
                    if (!isNaN(t) && !isNaN(h)) {
                        minTemp = Math.min(minTemp, t); maxTemp = Math.max(maxTemp, t);
                        document.getElementById('val-min').textContent = minTemp.toFixed(1) + " °C";
                        document.getElementById('val-max').textContent = maxTemp.toFixed(1) + " °C";
                        
                        let gamma = (17.27 * t) / (237.7 + t) + Math.log(h / 100.0);
                        let dew = (237.7 * gamma) / (17.27 - gamma);
                        document.getElementById('val-dew').textContent = dew.toFixed(1);
                        
                        let feels = t + 0.05 * h - 2.5;
                        document.getElementById('val-feels').textContent = (t > 22 ? feels : t).toFixed(1) + " °C";

                        histTemp.push(t); if (histTemp.length > MAX_PTS) histTemp.shift();
                        drawSmoothSparkline('chart-temp', histTemp, '#ffffff', 'rgba(255, 255, 255, 0.25)');
                        
                        histDew.push(dew); if (histDew.length > MAX_PTS) histDew.shift();
                        drawSmoothSparkline('chart-dew', histDew, '#0d9488', 'rgba(13, 148, 136, 0.2)');

                        let archOffset = 109.95 - (Math.min(100, h) / 100.0) * 109.95;
                        document.getElementById('arch-val').style.strokeDashoffset = archOffset;
                    }

                    if (!isNaN(parseFloat(d.light))) {
                        histLight.push(parseFloat(d.light)); if (histLight.length > MAX_PTS) histLight.shift();
                        drawSmoothSparkline('chart-light', histLight, '#ca8a04', 'rgba(202, 138, 4, 0.2)');
                    }
                    if (!isNaN(parseFloat(d.pressure))) {
                        histPres.push(parseFloat(d.pressure)); if (histPres.length > MAX_PTS) histPres.shift();
                        drawSmoothSparkline('chart-pres', histPres, '#9333ea', 'rgba(147, 51, 234, 0.2)');
                    }

                    document.getElementById('val-power').textContent = d.powerSource.split(' ')[0] + " Power";
                    document.getElementById('val-power-sub').textContent = d.batteryPct >= 0 ? "(Battery Active)" : "(No Battery Connected)";
                    document.getElementById('val-bat-pct').textContent = d.batteryPct >= 0 ? d.batteryPct + "%" : "No Battery";
                    document.getElementById('val-bat-volts').textContent = d.batteryPct >= 0 ? "(" + d.batteryVolts + " V)" : "(USB Bus Powered)";

                    let idx = parseInt(d.gasIndex);
                    if (!isNaN(idx)) {
                        let pct = Math.min(100, Math.max(0, (idx / 400.0) * 100));
                        document.getElementById('aqi-thumb').style.left = `calc(${pct}% - 8px)`;
                    }

                    document.getElementById('status-smoke').textContent = d.smokeStatus;
                    document.getElementById('status-light').textContent = d.lightType.split('/')[0];
                    document.getElementById('status-sys').textContent = d.systemStatus.split('(')[0];

                    document.getElementById('dev-board').textContent = d.board;
                    document.getElementById('dev-fw').textContent = d.fw;
                    document.getElementById('dev-ip').textContent = d.ip;
                    document.getElementById('dev-up').textContent = d.uptime;
                    
                    document.getElementById('st-dht').innerHTML = d.dht ? "OK" : "<span style='color:#dc2626;'>ERR</span>";
                    document.getElementById('st-bmp').innerHTML = d.bmp ? "OK" : "<span style='color:#dc2626;'>ERR</span>";
                    document.getElementById('st-bh').innerHTML = d.bh1750 ? "OK" : "<span style='color:#dc2626;'>ERR</span>";
                    document.getElementById('st-mq').innerHTML = d.mq135 ? "OK" : "<span style='color:#dc2626;'>ERR</span>";
                    
                    let sensList = document.getElementById('mod-sens').querySelector('.modal-content');
                    if(!document.getElementById('st-core')) {
                        sensList.innerHTML += `<div class="list-item"><span>ESP32 Core Heat:</span><strong id="st-core">--</strong></div>`;
                    }
                    document.getElementById('st-core').innerHTML = d.coreTemp > 55.0 ? `<span style='color:#dc2626;'>${d.coreTemp} °C (HOT)</span>` : `${d.coreTemp} °C`;

                } else {
                    badge.classList.add('offline'); txt.textContent = "OFFLINE";
                }
            }
        };
        xhr.open("GET", "/data", true); xhr.timeout = 800; xhr.send();
    }
    setInterval(fetchData, 1000); fetchData();
</script>
</body>
</html>
)rawliteral";

#endif // WEBPAGE_H
