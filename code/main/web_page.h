/* web_page.h */
#pragma once
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Mobilan Ehsan</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">

  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 0; padding: 0;
      background: #000; color: white;
      display: flex; justify-content: center; align-items: center;
      height: 100vh; overflow: hidden;
      flex-direction: column;
    }

    .page {
      display: none;
      width: 100%; height: 100%;
      text-align: center;
    }

    .active {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
    }

    .footer {
      position: absolute;
      bottom: 8px;
      width: 100%;
      text-align: center;
      font-size: 0.8em;
      color: #aaa;
    }

    /* Back button */
    .backBtn {
      position: absolute;
      top: 10px; left: 10px;
      background: #444; color: white;
      border: none; border-radius: 8px;
      padding: 8px 14px; font-size: 1em;
    }

    /* Halaman Home */
    #home {
      background: url('https://picsum.photos/800/480?blur=3') no-repeat center center;
      background-size: cover; color: white;
    }

    #home h1 {
      font-size: 2em;
      margin-bottom: 20px;
      text-shadow: 0 0 5px black;
    }

    #status { margin: 10px; font-weight: bold; }

    #logo {
      width: 120px; height: auto;
      margin-bottom: 20px;
      filter: drop-shadow(0 0 4px #000);
    }

    /* Tombol umum */
    button {
      padding: 15px 25px;
      font-size: 1.2em;
      border: none; border-radius: 12px;
      background: #0d6efd; color: white;
      margin: 10px;
    }
    button:active { background: #0b5ed7; }

    /* Joystick / TrackTank */
    #joystickContainer, #tracktankContainer {
      position: relative;
      width: 80vw; max-width: 300px;
      height: 80vw; max-height: 300px;
      margin: 20px auto;
      background: #eee; border-radius: 50%;
      touch-action: none;
    }

    #stick {
      position: absolute;
      width: 25%; height: 25%;
      background: #333;
      border-radius: 50%;
      top: 37.5%; left: 37.5%;
      opacity: 0.7;
      transition: transform 0.05s;
    }

    #speedSlider {
      width: 80%;
      max-width: 300px;
    }

    #controlPanel { margin-top: 20px; }
  </style>
</head>

<body>

  <!-- ================= HOME ================= -->
  <div id="home" class="page active">
    <img id="logo" src="logo.png" alt="Muhun Project Logo">
    <h1>Mobilan Ehsan</h1>
    <p id="status">Status: <span id="connStatus">Disconnect</span></p>
    <button onclick="goPage('mode')">Mulai</button>
  </div>

  <!-- ================= MODE SELECTION ================= -->
  <div id="mode" class="page">
    <button class="backBtn" onclick="goBack()">Back</button>
    <h2>Pilih Mode</h2>
    <select id="modeSelect">
      <option value="joystick">Joystick</option>
      <option value="tracktank">TrackTank</option>
    </select>
    <button onclick="startControl()">Lanjut</button>
  </div>

  <!-- ================= JOYSTICK MODE ================= -->
  <div id="joystickPage" class="page">
    <button class="backBtn" onclick="goBack()">Back</button>
    <h2>Joystick Mode</h2>

    <!-- Kontrol LED & Lagu -->
    <div>
      <button onclick="sendCmd('LED_ON')">LED ON</button>
      <button onclick="sendCmd('LED_OFF')">LED OFF</button>
      <button onclick="sendCmd('SONG1')">Lagu 1</button>
      <button onclick="sendCmd('SONG2')">Lagu 2</button>
      <button onclick="sendCmd('STOP_SONG')">Stop Lagu</button>
    </div>

    <!-- Area Joystick -->
    <div id="joystickContainer">
      <div id="stick"></div>
    </div>

    <!-- Speed Control -->
    <label>Speed: <span id="speedVal">512</span></label><br>
    <input type="range" id="speedSlider" min="0" max="1023" value="512" oninput="updateSpeed(this.value)">
  </div>

  <!-- ================= TRACKTANK MODE ================= -->
  <div id="tracktankPage" class="page">
    <button class="backBtn" onclick="goBack()">Back</button>
    <h2>TrackTank Mode</h2>
    <div id="controlPanel">
      <button onclick="sendCmd('FWD')">Maju</button><br>
      <button onclick="sendCmd('LEFT')">Kiri</button>
      <button onclick="sendCmd('RIGHT')">Kanan</button><br>
      <button onclick="sendCmd('BACK')">Mundur</button>
      <button onclick="sendCmd('STOP')">Stop</button>
    </div>
  </div>

  <!-- ================= FOOTER ================= -->
  <div class="footer">
    by: muhunproject@gmail.com | V1.11.2025
  </div>

  <!-- ================= SCRIPT ================= -->
  <script>
    var ws;

    // --- WebSocket ---
    function startWS() {
      ws = new WebSocket("ws://" + location.hostname + ":81/");
      ws.onopen  = () => { document.getElementById('connStatus').innerText = "Connected"; };
      ws.onclose = () => { 
        document.getElementById('connStatus').innerText = "Disconnect"; 
        setTimeout(startWS, 1000); 
      };
    }
    startWS();

    // --- Kirim perintah ke server ---
    function sendCmd(cmd) {
      if (ws && ws.readyState === 1) ws.send(cmd);
    }

    // --- Atur kecepatan motor ---
    function updateSpeed(val) {
      document.getElementById('speedVal').innerText = val;
      sendCmd("SPEED:" + val);
    }

    // --- Navigasi halaman ---
    let pageHistory = [];

    function goPage(id) {
      let current = document.querySelector('.page.active');
      if (current) pageHistory.push(current.id);
      document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
      document.getElementById(id).classList.add('active');
    }

    function goBack() {
      if (pageHistory.length > 0) {
        let prev = pageHistory.pop();
        document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
        document.getElementById(prev).classList.add('active');
      }
    }

    // --- Pilih mode kontrol ---
    function startControl() {
      let mode = document.getElementById('modeSelect').value;
      if (mode == "joystick") goPage('joystickPage');
      else goPage('tracktankPage');
      sendCmd("MODE:" + mode);
    }

    // --- Joystick logic ---
    const stick = document.getElementById('stick');
    const container = document.getElementById('joystickContainer');
    let origin = { x: 0, y: 0 }, dragging = false;

    if (container) {
      container.addEventListener('touchstart', (e) => {
        dragging = true;
        const rect = container.getBoundingClientRect();
        origin.x = rect.left + rect.width / 2;
        origin.y = rect.top + rect.height / 2;
      });

      container.addEventListener('touchmove', (e) => {
        if (!dragging) return;
        const touch = e.touches[0];
        let dx = touch.clientX - origin.x;
        let dy = touch.clientY - origin.y;
        let maxDist = container.offsetWidth / 2 - stick.offsetWidth / 2;
        let dist = Math.sqrt(dx * dx + dy * dy);
        if (dist > maxDist) { dx = dx * maxDist / dist; dy = dy * maxDist / dist; }
        stick.style.transform = `translate(${dx}px,${dy}px)`;

        let cmd = "STOP";
        if (Math.abs(dx) < 20 && Math.abs(dy) < 20) cmd = "STOP";
        else if (Math.abs(dy) > Math.abs(dx)) cmd = (dy < 0) ? "FWD" : "BACK";
        else cmd = (dx < 0) ? "LEFT" : "RIGHT";

        sendCmd(cmd);
      });

      container.addEventListener('touchend', () => {
        dragging = false;
        stick.style.transform = "translate(0px,0px)";
        sendCmd("STOP");
      });
    }
  </script>
</body>
</html>
)rawliteral";
