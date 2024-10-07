//dm3D == display3d.mgrDraw3D() !!!
//---------------------------------------

dm3D.initGraphics = function() {

  dm3D.initCamera();

  dm3D.scene( new THREE.Scene() );

  dm3D.initRenderer();

  dm3D.initControls();

  dm3D.groupOfVertices( new THREE.Group() );

  dm3D.groupOfTracks( new THREE.Group() );

  dm3D.initVertexProperties();

  dm3D.initTrackLineProperties();

};
//------------------------------------------------------------------------------

dm3D.initCamera = function() {

  const primVertDrawPos = dm3D.primVertDrawPos();

  dm3D.cameraInitPositions([
    new THREE.Vector3(primVertDrawPos.x - 200,
                      primVertDrawPos.y + 2000,
                      primVertDrawPos.z + 200),

    new THREE.Vector3(primVertDrawPos.x - 2000,
                      primVertDrawPos.y + 200,
                      primVertDrawPos.z + 200),

    new THREE.Vector3(primVertDrawPos.x - 200,
                      primVertDrawPos.y + 200,
                      primVertDrawPos.z + 7000)
  ]);

  dm3D.camera( new THREE.OrthographicCamera(primVertDrawPos.z - 1800,
                                            primVertDrawPos.z + 4200,
                                            primVertDrawPos.y + 1854,
                                            primVertDrawPos.y - 1854,
                                            primVertDrawPos.x - 50000,
                                            primVertDrawPos.x + 150000) );
};
//------------------------------------------------------------------------------

dm3D.resetCamera = function() {

  const ip = dm3D.view();

  dm3D.camera().position.copy(dm3D.cameraInitPositions()[ip]);

  dm3D.camera().up.copy( dm3D.cameraInitUpDirs(ip) );

  const primVertDrawPos = dm3D.primVertDrawPos();

  dm3D.camera().lookAt(primVertDrawPos);

};
//------------------------------------------------------------------------------

dm3D.initRenderer = function() {

  const canvWidth  = 800;
  const canvHeight = 0.618*canvWidth;

  const canvas3D = document.getElementById("canvas-3D");

  dm3D.renderer( new THREE.WebGLRenderer( { canvas: canvas3D,
                                             antialias: true,
                                             alpha: true } ) );

  dm3D.renderer().setPixelRatio(window.devicePixelRatio);

  dm3D.renderer().setSize(canvWidth, canvHeight);

  dm3D.renderer().setClearColor(0x000000, 1);

  dm3D.renderer().gammaInput  = true;
  dm3D.renderer().gammaOutput = true;

};
//------------------------------------------------------------------------------

dm3D.initControls = function() {

  dm3D.tbControls( new THREE.TrackballControls(dm3D.camera(), dm3D.renderer().domElement) );

  dm3D.tbControls().zoomSpeed = 1.5;
  dm3D.tbControls().rotateSpeed = 1.0;
  dm3D.tbControls().panSpeed = 0.2;

  dm3D.tbControls().staticMoving = true;
  dm3D.tbControls().dynamicDampingFactor = 0.3;

};
//------------------------------------------------------------------------------

dm3D.initVertexProperties = function() {

  dm3D.vertexGeometry( new THREE.SphereGeometry(20, 32, 32) );

  dm3D.vertexMaterial( new THREE.MeshBasicMaterial({ color: Vertex.colorFor3D() }) );

};
//------------------------------------------------------------------------------

dm3D.initTrackLineProperties = function() {

  dm3D.trackLinePars()[1] = { // for a muon track

    color:  Track3D.colors(1),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[2] = { // for an hadron track

    color:  Track3D.colors(2),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[3] = { // for an electron track

    color:  Track3D.colors(3),
    length: 3*1300,
    width:  12

  };

  dm3D.trackLinePars()[4] = { // for a black track

    color:  Track3D.colors(4),
    length: 1*1300,
    width:  17

  };

  dm3D.trackLinePars()[5] = { // for a back black track

    color:  Track3D.colors(5),
    length: 1*1300,
    width:  17

  };

  dm3D.trackLinePars()[6] = { // for a gray track

    color:  Track3D.colors(6),
    length: 1.5*1300,
    width:  17

  };

  dm3D.trackLinePars()[7] = { // for a back gray track

    color:  Track3D.colors(7),
    length: 1.5*1300,
    width:  17

  };

  dm3D.trackLinePars()[8] = { // for a tau-lepton track

    color:  Track3D.colors(8),
    length: 0.7*1300,
    width:  17

  };

  dm3D.trackLinePars()[9] = { // for tracks of hadrons

    color:  Track3D.colors(9),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[10] = { // for tracks of hadrons

    color:  Track3D.colors(10),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[11] = { // for tracks of hadrons

    color:  Track3D.colors(11),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[12] = { // for tracks of hadrons

    color:  Track3D.colors(12),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[13] = { // for tracks of hadrons

    color:  Track3D.colors(13),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[14] = { // for tracks of hadrons

    color:  Track3D.colors(14),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[15] = { // for tracks of hadrons

    color:  Track3D.colors(15),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[16] = { // for e+/e- tracks

    color:  Track3D.colors(16),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[17] = { // for e+/e- tracks

    color:  Track3D.colors(17),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[18] = { // for e+/e- tracks

    color:  Track3D.colors(18),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[19] = { // for e+/e- tracks

    color:  Track3D.colors(19),
    length: 10*1300,
    width:  12

  };

  dm3D.trackLinePars()[20] = { // for tracks of hadrons

    color:  Track3D.colors(20),
    length: 10*1300,
    width:  12

  };

};
//------------------------------------------------------------------------------

dm3D.prepareAndDrawEvent = function(resetCamera) {

  setTimeout( function() { dm3D.drawEvent(resetCamera); }, 100 );

};
//------------------------------------------------------------------------------

dm3D.drawEvent = function(resetCamera) {

  dm3D.drawVertices();

  dm3D.drawTracks();

  if (resetCamera) {

    dm3D.tbControls().reset();

    dm3D.resetCamera();

    dm3D.camera().updateProjectionMatrix();

  }

  dm3D.render();

};
//------------------------------------------------------------------------------

dm3D.render = function() {

  dm3D.renderer().render( dm3D.scene(), dm3D.camera() );

};
//------------------------------------------------------------------------------

dm3D.runInteractiveMode = function() {

  requestAnimationFrame(dm3D.runInteractiveMode);

  dm3D.tbControls().update();

  dm3D.render();

};
//------------------------------------------------------------------------------

dm3D.drawVertices = function() {

  const evVertices = display3d.event().vertices3D();

  const primVertRealPos = evVertices[0].pos();

  const primVertDrawPos = dm3D.primVertDrawPos();

  const nbOfVertices = evVertices.length;

  for (let iv = 0; iv < nbOfVertices; iv++) {

    const vertexPoint = new THREE.Mesh( dm3D.vertexGeometry(), dm3D.vertexMaterial() );

    const vertRealPos = evVertices[iv].pos();

    vertexPoint.position.x = primVertDrawPos.x + vertRealPos[0] - primVertRealPos[0]; // Relative vertex position
    vertexPoint.position.y = primVertDrawPos.y + vertRealPos[1] - primVertRealPos[1]; // with respect to
    vertexPoint.position.z = primVertDrawPos.z + vertRealPos[2] - primVertRealPos[2]; // the primary interaction vertex!

    dm3D.groupOfVertices().add(vertexPoint);

  }

  dm3D.scene().add(dm3D.groupOfVertices());

};
//------------------------------------------------------------------------------

dm3D.drawTracks = function() {

  const primVertRealPos = display3d.event().vertices3D()[0].pos();

  const primVertDrawPos = dm3D.primVertDrawPos();

  const evTracks = display3d.event().tracks3D();

  const nbOfTracks = evTracks.length;

  for (let it = 0; it < nbOfTracks; it++) {

    const iTrack = evTracks[it];

    const trPos1 = [0, 0, 0]; // Just a 1d array initialization
    const trPos2 = [0, 0, 0]; // Just a 1d array initialization

    for (let ip = 0; ip < 3; ip++) {

      trPos1[ip] = iTrack.pos1()[ip] - primVertRealPos[ip]; // Relative track positions with respect to
      trPos2[ip] = iTrack.pos2()[ip] - primVertRealPos[ip]; // the primary interaction vertex!

    }

    const trPars = dm3D.trackLinePars()[iTrack.partId()];

    const trackLine = new three3DExtras.tubeLine(trPos1, trPos2, trPars.width, trPars.color); 

    dm3D.groupOfTracks().add(trackLine.getObject3D());

  }

  dm3D.scene().add(dm3D.groupOfTracks());

};
//------------------------------------------------------------------------------

dm3D.onEventChange = function() {

  dm3D.updateCanvas(1);

  dm3D.displayEventInfo();

  dm3D.runInteractiveMode();

};
//------------------------------------------------------------------------------

dm3D.displayEventInfo = function() {

  const evId = display3d.event().id();

  const inputEvent3D = document.getElementById("input-event-3D");

  inputEvent3D.value = evId;

  const dateFormatOptions = {

    timeZone: "UTC",
    hour12:    false,

    year:     "numeric",
    month:    "short",
    day:      "2-digit",
    hour:     "2-digit",
    minute:   "2-digit"

  }

  const titleBeg = "Event: " + evId + ", " +
                           display3d.event().date().toLocaleString("en-US", dateFormatOptions) +
                           " (UTC),";

  $("#span-canvas-3D-title").text(titleBeg + " Tracks reconstructed in emulsion");

};
//-----------------------------------------------------------------------------

dm3D.updateCanvas = function(resetCamera) {

  if (dm3D.camera() === null) {

    dm3D.initGraphics(); //!!!

  }

  dm3D.clearCanvas();

  dm3D.prepareAndDrawEvent(resetCamera);

};
//------------------------------------------------------------------------------

dm3D.clearCanvas = function() {

  dm3D.clearGroupOfVertices();

  dm3D.clearGroupOfTracks();

};
//------------------------------------------------------------------------------
