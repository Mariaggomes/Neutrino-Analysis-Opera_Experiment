class Display3d { // Browser-based 3D event display

  constructor() {

    this._evListNuTau = [];   // Array of OPERA nu_tau event IDs

    this._evIndex    = -1;    // Index of the loaded event in the array (from 0 to evList.length - 1)
    this._evIndexMax = -1;    // Max index of the loaded event in the array (=== evList.length - 1)
    this._event      = {};    // Loaded (displayed) event

    this._mgrDraw3D = {};    // Manager hired for drawing of (3D) tracks found in emulsion

  };

  evList(evsample, evlist) {

    if (evlist === undefined) return this._evListNuTau;

    this._evListNuTau = evlist;

    this._evIndex = 0;
    this._evIndexMax = evlist.length - 1;

  };

  evIndex(evindex) {

    if (evindex === undefined) return this._evIndex;

    this._evIndex = evindex;

  };

  evIndexMax(evindexmax) {

    if (evindexmax === undefined) return this._evIndexMax;

    this._evIndexMax = evindexmax;

  };

  event(ev) {

    if (ev === undefined) return this._event;

    this._event = ev;

  };

  resetEvent() { this._event = new Event(); };

  loadPrevOrNextEvent(dIndex) {

    if (dIndex === undefined) dIndex = 1; // by default load next event in the event list

    let newIndex = this._evIndex + dIndex;

    this._evIndex = newIndex;

    let evID = this.evList(1)[newIndex];

    changeScrLoadEvent(evID); // External function defined in the loadEvent.js file

  };

  mgrDraw3D(mgrdraw) {

    if (mgrdraw === undefined) return this._mgrDraw3D;

    this._mgrDraw3D = mgrdraw;

  };

};
