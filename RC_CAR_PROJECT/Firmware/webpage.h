#ifndef WEBPAGE_H
#define WEBPAGE_H

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta
        name="viewport"
        content="width=device-width, initial-scale=1.0">
    <title>ESP32 RC Car</title>
    <style>
/* ===========================================
   RESET
=========================================== */

*{
    margin:0;
    padding:0;
    box-sizing:border-box;
}

:root{

    --bg:#08111f;
    --card:rgba(18,28,45,.65);
    --border:rgba(255,255,255,.08);

    --primary:#3b82f6;
    --primary-hover:#2563eb;

    --success:#22c55e;
    --danger:#ef4444;
    --warning:#f59e0b;

    --text:#f8fafc;
    --secondary:#94a3b8;

    --radius:24px;

}

body{

    font-family:
    system-ui,
    -apple-system,
    BlinkMacSystemFont,
    "Segoe UI",
    sans-serif;

    background:var(--bg);

    color:var(--text);

    overflow-x:hidden;

    min-height:100vh;

    display:flex;

    justify-content:center;

    align-items:center;

    padding:25px;

}

/* ===========================================
   BACKGROUND
=========================================== */

.background{

    position:fixed;

    inset:0;

    overflow:hidden;

    z-index:-1;

}

.blur{

    position:absolute;

    width:350px;

    height:350px;

    border-radius:50%;

    filter:blur(120px);

    opacity:.25;

}

.blur1{

    background:#2563eb;

    top:-80px;

    left:-120px;

}

.blur2{

    background:#9333ea;

    right:-120px;

    bottom:-100px;

}

/* ===========================================
   MAIN DASHBOARD
=========================================== */

.dashboard{

    width:100%;

    max-width:420px;

    background:var(--card);

    backdrop-filter:blur(25px);

    border:1px solid var(--border);

    border-radius:30px;

    padding:28px;

    box-shadow:

    0 25px 60px rgba(0,0,0,.45);

}

/* ===========================================
   HEADER
=========================================== */

.header{

    display:flex;

    justify-content:space-between;

    align-items:center;

    margin-bottom:28px;

}

.header h1{

    font-size:28px;

    font-weight:700;

}

.header p{

    color:var(--secondary);

    margin-top:6px;

}

.status{

    display:flex;

    align-items:center;

    gap:8px;

    font-size:15px;

}

.dot{

    width:12px;

    height:12px;

    background:var(--success);

    border-radius:50%;

    box-shadow:

    0 0 15px var(--success);

}

/* ===========================================
   INFO CARDS
=========================================== */

.cards{

    display:grid;

    grid-template-columns:1fr 1fr;

    gap:15px;

    margin-bottom:30px;

}

.card{

    background:rgba(255,255,255,.05);

    border-radius:20px;

    padding:18px;

    border:1px solid rgba(255,255,255,.05);

}

.cardTitle{

    color:var(--secondary);

    font-size:14px;

    margin-bottom:15px;

}
.battery{
    display:flex;
    align-items:center;
    gap:15px;
}
.batteryIcon{
    width:42px;
    height:22px;
    border:2px solid white;
    border-radius:5px;
    position:relative;
}
.batteryIcon::after{
    content:"";
    position:absolute;
    right:-6px;
    top:5px;
    width:4px;
    height:8px;
    background:white;
    border-radius:2px;
}
.batteryFill{
    height:100%;
    width:100%;
    background:var(--success);
    border-radius:2px;
}
#batteryPercent{
    font-size:22px;
    font-weight:600;
}
.wifi{
    font-size:24px;
    margin-bottom:8px;
}
#ip{
    color:var(--secondary);
}
/* ===========================================
   D-PAD
=========================================== */

.controller{

    display:flex;
    flex-direction:column;
    align-items:center;
    gap:18px;

    margin-bottom:35px;

}

.middle{

    display:flex;
    gap:18px;

}

.direction,
.stop{

    width:78px;
    height:78px;

    border:none;

    border-radius:50%;

    cursor:pointer;

    color:white;

    font-size:28px;

    transition:.25s ease;

    display:flex;
    justify-content:center;
    align-items:center;

    user-select:none;

}

.direction{

    background:linear-gradient(
        145deg,
        #3b82f6,
        #2563eb
    );

    box-shadow:

    0 10px 25px rgba(37,99,235,.35);

}

.direction:hover{

    transform:translateY(-4px);

    box-shadow:

    0 15px 30px rgba(37,99,235,.55);

}

.direction:active{

    transform:scale(.92);

}

.stop{

    background:linear-gradient(
        145deg,
        #ef4444,
        #dc2626
    );

    box-shadow:

    0 12px 30px rgba(239,68,68,.45);

}

.stop:hover{

    transform:scale(1.08);

}

.stop:active{

    transform:scale(.90);

}


/* ===========================================
   SPEED CARD
=========================================== */

.speedCard{

    background:rgba(255,255,255,.05);

    border-radius:20px;

    padding:22px;

    margin-bottom:30px;

    border:1px solid rgba(255,255,255,.05);

}

.speedHeader{

    display:flex;

    justify-content:space-between;

    align-items:center;

    margin-bottom:18px;

    font-weight:600;

}

#speedText{

    color:#38bdf8;

    font-size:22px;

}


/* Slider */

#speedSlider{

    width:100%;

    cursor:pointer;

    appearance:none;

    height:8px;

    border-radius:20px;

    background:#334155;

}

/* Chrome */

#speedSlider::-webkit-slider-thumb{

    appearance:none;

    width:22px;

    height:22px;

    border-radius:50%;

    background:#3b82f6;

    border:4px solid white;

    cursor:pointer;

    transition:.2s;

}

#speedSlider::-webkit-slider-thumb:hover{

    transform:scale(1.25);

}


/* Firefox */

#speedSlider::-moz-range-thumb{

    width:22px;

    height:22px;

    border:none;

    border-radius:50%;

    background:#3b82f6;

}


/* ===========================================
   FEATURE BUTTONS
=========================================== */

.features{

    display:grid;

    grid-template-columns:1fr 1fr;

    gap:15px;

    margin-bottom:28px;

}

.features button{

    padding:18px;

    border:none;

    border-radius:18px;

    cursor:pointer;

    color:white;

    font-size:16px;

    font-weight:600;

    transition:.25s;

}

#lightButton{

    background:linear-gradient(
        145deg,
        #f59e0b,
        #d97706
    );

}

#hornButton{

    background:linear-gradient(
        145deg,
        #10b981,
        #059669
    );

}

.features button:hover{

    transform:translateY(-4px);

    box-shadow:

    0 12px 25px rgba(255,255,255,.12);

}

.features button:active{

    transform:scale(.95);

}


/* ===========================================
   FOOTER
=========================================== */

footer{

    display:flex;

    justify-content:space-between;

    align-items:center;

    color:#94a3b8;

    font-size:13px;

}


/* ===========================================
   RESPONSIVE
=========================================== */

@media(max-width:450px){

    body{

        padding:15px;

    }

    .dashboard{

        padding:22px;

    }

    .direction,
    .stop{

        width:65px;
        height:65px;

        font-size:22px;

    }

    .middle{

        gap:14px;

    }

    .cards{

        grid-template-columns:1fr;

    }

    footer{

        flex-direction:column;

        gap:8px;

    }

}
/* ===========================================
   GLOW ANIMATIONS
=========================================== */

@keyframes glowBlue{

    0%{
        box-shadow:0 0 0 rgba(59,130,246,0);
    }

    50%{
        box-shadow:
        0 0 15px rgba(59,130,246,.8),
        0 0 35px rgba(59,130,246,.45);
    }
    100%{
        box-shadow:0 0 0 rgba(59,130,246,0);
    }
}
@keyframes glowRed{
    0%{
        box-shadow:0 0 0 rgba(239,68,68,0);
    }
    50%{
        box-shadow:
        0 0 15px rgba(239,68,68,.8),
        0 0 35px rgba(239,68,68,.45);
    }
    100%{
        box-shadow:0 0 0 rgba(239,68,68,0);
    }
}
.direction.active{
    animation:glowBlue .6s ease;
}
.stop.active{
    animation:glowRed .6s ease;
}
/* ===========================================
   BATTERY COLORS
=========================================== */
.battery-green{
    background:#22c55e;
}
.battery-yellow{
    background:#f59e0b;
}
.battery-red{
    background:#ef4444;
}
/* ===========================================
   CONNECTION STATUS
=========================================== */
.connected .dot{
    background:#22c55e;
    box-shadow:0 0 18px #22c55e;
}
.disconnected .dot{
    background:#ef4444;
    box-shadow:0 0 18px #ef4444;
}
/* ===========================================
   LIGHT BUTTON STATES
=========================================== */
#lightButton.on{
    background:#facc15;
    color:#111827;
    box-shadow:
        0 0 18px rgba(250,204,21,.8);
}
#lightButton.off{
    opacity:.75;
}
/* ===========================================
   HORN ACTIVE
=========================================== */
#hornButton.active{
    background:#059669;
    transform:scale(.96);
    box-shadow:
        0 0 18px rgba(16,185,129,.8);
}
/* ===========================================
   CARD HOVER
=========================================== */
.card{
    transition:.25s;
}
.card:hover{
    transform:translateY(-4px);
    border-color:rgba(59,130,246,.35);
}
/* ===========================================
   SCROLLBAR
=========================================== */
::-webkit-scrollbar{
    width:8px;
}
::-webkit-scrollbar-track{
    background:#111827;
}
::-webkit-scrollbar-thumb{
    background:#3b82f6;
    border-radius:10px;
}
/* ===========================================
   BUTTON RIPPLE EFFECT
=========================================== */
.direction,
.stop,
.features button{
    overflow:hidden;
    position:relative;
}
.direction::after,
.stop::after,
.features button::after{
    content:"";
    position:absolute;
    width:0;
    height:0;
    left:50%;
    top:50%;
    transform:translate(-50%,-50%);
    background:rgba(255,255,255,.2);
    border-radius:50%;
    transition:.45s;
}
.direction:active::after,
.stop:active::after,
.features button:active::after{
    width:180px;
    height:180px;
}
/* ===========================================
   SMOOTH TRANSITIONS
=========================================== */
button,
.card,
.status,
#batteryLevel{
    transition:.25s ease;
}

</style>
</head>
<body>
    <div class="background">
        <div class="blur blur1"></div>
        <div class="blur blur2"></div>
    </div>
    <main class="dashboard">
        <!-- Header -->
        <header class="header">
            <div>
                <h1>ESP32 RC CAR</h1>
                <p>HTTP Remote Controller</p>
            </div>
            <div class="status">
                <span class="dot"></span>
                Connected
            </div>
        </header>
        <!-- Information Cards -->
        <section class="cards">
            <div class="card">
                <div class="cardTitle">
                    Battery
                </div>
                <div class="battery">
                    <div class="batteryIcon">
                        <div
                            id="batteryLevel"
                            class="batteryFill">
                        </div>
                    </div>
                    <span id="batteryPercent">
                        100%
                    </span>
                </div>
            </div>
            <div class="card">
                <div class="cardTitle">
                    WiFi
                </div>
                <div class="wifi">
                    📶 RC_CAR
                </div>
                <small id="ip">
                    192.168.4.1
                </small>
            </div>
        </section>
        <!-- D Pad -->
        <section class="controller">
            <button
                id="forward"
                class="direction up">
                ▲
            </button>
            <div class="middle">
                <button
                    id="left"
                    class="direction">
                    ◀
                </button>
                <button
                    id="stop"
                    class="stop">
                    ■
                </button>
                <button
                    id="right"
                    class="direction">
                    ▶
                </button>
            </div>
            <button
                id="backward"
                class="direction down">
                ▼
            </button>
        </section>
        <!-- Speed -->
        <section class="speedCard">
            <div class="speedHeader">
                <span>
                    Speed
                </span>
                <span id="speedText">
                    70%
                </span>
            </div>
            <input
                type="range"
                min="0"
                max="255"
                value="180"
                id="speedSlider">
        </section>
        <!-- Features -->
        <section class="features">
            <button id="lightButton">
                💡 Headlights
            </button>
            <button id="hornButton">
                📢 Horn
            </button>
        </section>
        <!-- Footer -->
        <footer>
            <div>
                Firmware v1.0
            </div>
            <div>
                ESP32 HTTP Server
            </div>
        </footer>
    </main>
    <script>
// ==========================
// CONFIG
// ==========================

// Change this later if needed
const BASE_URL = "";


// ==========================
// ELEMENTS
// ==========================

const forward = document.getElementById("forward");
const backward = document.getElementById("backward");
const left = document.getElementById("left");
const right = document.getElementById("right");
const stop = document.getElementById("stop");

const horn = document.getElementById("hornButton");
const lights = document.getElementById("lightButton");

const slider = document.getElementById("speedSlider");

const speedText = document.getElementById("speedText");

const batteryText = document.getElementById("batteryPercent");

const batteryLevel = document.getElementById("batteryLevel");

const status = document.querySelector(".status");

let lightsOn = false;


// ==========================
// HTTP REQUEST
// ==========================

async function send(endpoint){

    try{

        await fetch(BASE_URL + endpoint);

    }

    catch(error){

        console.log(error);

    }

}


// ==========================
// BUTTON ANIMATION
// ==========================

function animate(button){

    button.classList.add("active");

    setTimeout(()=>{

        button.classList.remove("active");

    },200);

}


// ==========================
// DIRECTION BUTTONS
// ==========================

function hold(button,startCommand){

    button.addEventListener("pointerdown",()=>{

        animate(button);

        send(startCommand);

    });

    button.addEventListener("pointerup",()=>{

        send("/stop");

    });

    button.addEventListener("pointerleave",()=>{

        send("/stop");

    });

}


// ==========================
// DRIVE CONTROLS
// ==========================

hold(forward,"/forward");

hold(backward,"/backward");

hold(left,"/left");

hold(right,"/right");


// STOP BUTTON

stop.addEventListener("click",()=>{

    animate(stop);

    send("/stop");

});


// ==========================
// SPEED
// ==========================

slider.addEventListener("input",()=>{

    speedText.innerText =

    Math.round(

    slider.value/255*100

    )+"%";

});


slider.addEventListener("change",()=>{

    send("/speed?value="+slider.value);

});


// ==========================
// HEADLIGHTS
// ==========================

lights.addEventListener("click",()=>{

    lightsOn=!lightsOn;

    if(lightsOn){

        lights.classList.add("on");

        lights.classList.remove("off");

        send("/light/on");

    }

    else{

        lights.classList.remove("on");

        lights.classList.add("off");

        send("/light/off");

    }

});


// ==========================
// HORN
// ==========================

horn.addEventListener("pointerdown",()=>{

    horn.classList.add("active");

    send("/horn/on");

});

horn.addEventListener("pointerup",()=>{

    horn.classList.remove("active");

    send("/horn/off");

});

horn.addEventListener("pointerleave",()=>{

    horn.classList.remove("active");

    send("/horn/off");

});


// ==========================
// BATTERY UI
// ==========================

function updateBattery(percent){

    batteryText.innerText = percent+"%";

    batteryLevel.style.width = percent+"%";

    batteryLevel.className="batteryFill";

    if(percent>60){

        batteryLevel.classList.add("battery-green");

    }

    else if(percent>25){

        batteryLevel.classList.add("battery-yellow");

    }

    else{

        batteryLevel.classList.add("battery-red");
    }
}
// ==========================
// STATUS
// ==========================

function updateStatus(connected){
    if(connected){
        status.classList.remove("disconnected");
        status.classList.add("connected");
        status.innerHTML=`
        <span class="dot"></span>
        Connected
        `;
    }
    else{
        status.classList.remove("connected");
        status.classList.add("disconnected");
        status.innerHTML=`
        <span class="dot"></span>
        Offline
        `;
    }
}
// ==========================
// ESP32 STATUS
// ==========================

async function refresh(){

    try{
        const response=await fetch(BASE_URL+"/status");
        const data=await response.json();
        updateBattery(data.battery);
        updateStatus(true);
    }
    catch{
        updateStatus(false);
    }
}
setInterval(refresh,1000);
// ==========================
// INITIALIZE
// ==========================
updateBattery(100);
updateStatus(true);

</script>
</body>
</html>

)rawliteral";

#endif
