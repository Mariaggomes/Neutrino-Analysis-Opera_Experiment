class MgrDraw3D { // Manager intended for drawing of vertices and (3D) tracks found in the emulsion

  constructor() {

    this._camera     = null;

    this._scene      = null;

    this._renderer   = null;    // Draws the scene on the screen (as it is seen by the camera)

    this._tbControls = null;    // Trackball controls can be used to pan and move the camera around

    this._view = 1;             // 0 - XZ, 1 - YZ, and 2 - XY

    //---

    this._primVertDrawPos = new THREE.Vector3(0, 0, 0); // Position of the primary vertex.
                                                        // The code of drawing functions should be properly
                                                        // modified in case change of this position is needed!!!

    this._cameraInitPositions = [];                     // Initialyzed in the initCamera() function!

    this._cameraInitUpDirs = [new THREE.Vector3(1, 0, 0),   // The 'up' directions of the camera for XZ,
                              new THREE.Vector3(0, 1, 0),   //                                       YZ,
                              new THREE.Vector3(0, 1, 0)];  //                                       and XY views

    this._vertexGeometry = {};

    this._vertexMaterial = {};

    this._groupOfVertices = {};   // three.js group of vertex points

    this._trackLinePars = [];     // Array of line parameters used for drawing of the 3D tracks

    this._groupOfTracks = {};     // three.js group of track lines

  };

  camera(cam) {

    if (cam === undefined) return this._camera;

    this._camera = cam;

  };

  scene(sc) {

    if (sc === undefined) return this._scene;

    this._scene = sc;

  };

  renderer(rend) {

    if (rend === undefined) return this._renderer;

    this._renderer = rend;

  };

  tbControls(cont) {

    if (cont === undefined) return this._tbControls;
    
    this._tbControls = cont;
  };

  view(ip) {

    if (ip === undefined) return this._view;

    this._view = ip;

  };

  vertexGeometry(vg) {

    if (vg === undefined) return this._vertexGeometry;

    this._vertexGeometry = vg;

  };

  vertexMaterial(vm) {

    if (vm === undefined) return this._vertexMaterial;

    this._vertexMaterial = vm;

  };

  groupOfVertices(group) {

    if (group === undefined) return this._groupOfVertices;

    this._groupOfVertices = group;

  };

  trackLinePars() { return this._trackLinePars; };

  groupOfTracks(group) {

    if (group === undefined) return this._groupOfTracks;

    this._groupOfTracks = group;

  };

  clearGroupOfVertices() {

    if (!this._groupOfVertices) return;

    let children = this._groupOfVertices.children;

    if (children) {
      for (let ic = children.length - 1; ic >= 0; ic--) {
        this._groupOfVertices.remove(children[ic]);
      }
    }

  };

  clearGroupOfTracks() {

    if (!this._groupOfTracks) return;

    let children = this._groupOfTracks.children;

    if (children) {
      for (let ic = children.length - 1; ic >= 0; ic--) {
        this._groupOfTracks.remove(children[ic]);
      }
    }

  };

  cameraInitPositions(initPositions) {

    if (initPositions === undefined) return this._cameraInitPositions;

    this._cameraInitPositions = initPositions;

  };

  cameraInitUpDirs(ip) {

    return this._cameraInitUpDirs[ip];

  };

  primVertDrawPos() { return this._primVertDrawPos; };

};
