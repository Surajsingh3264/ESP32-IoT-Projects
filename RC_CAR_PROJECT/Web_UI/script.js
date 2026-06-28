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
