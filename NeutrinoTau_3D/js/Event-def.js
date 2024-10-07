class Event { // OPERA event object will contain experimental data to be displayed in the main window

  constructor() {

    this._id = 0;             // OPERA event id

    this._date = {};          // The OPERA event time (millisecons since 01.01.1970)

    this._vertices3D = [];    // Array of vertices. [0] - the primary neutrino interaction vertex!

    this._tracks3D = [];      // Array of tracks.

  };

  id(jd) {

    if (jd === undefined) return this._id;

    this._id = jd;
  };

  date(ts) {

    if (ts === undefined) return this._date;

    this._date = new Date(ts);

  };

  vertices3D(vertices) {

    if (vertices === undefined) return this._vertices3D;

    this._vertices3D = vertices;

  };

  tracks3D(tracks) {

    if (tracks === undefined) return this._tracks3D;

    this._tracks3D = tracks;

  };

};
