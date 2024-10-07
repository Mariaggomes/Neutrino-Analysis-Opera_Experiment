class Track3D {

  constructor(id, partId, pos1, slopes, pos2) {

    this._id = id;

    this._partId = partId;   // particle Id

    this._pos1 = pos1;       // [posX, posY, posZ] Position of the first track point
                             // in the OPERA brick system of reference (in micrometers)

    this._pos2 = pos2;       // [posX, posY, posZ] Position of the second track point
                             // in the OPERA brick system of reference (in micrometers)
                             // This point is used only if slopes[0]==slopes[1]==1000000

    // Equations of a track:
    // X = Z*Axy[0] + Bxy[0], Y = Z*Axy[1] + Bxy[1]

    this._Axy = slopes; // [slopeXZ, slopeYZ] --- tangents of the track angles

  };

  id() { return this._id; };

  partId() { return this._partId; };

  pos1(ps) {

    if (ps === undefined) return this._pos1;

    this._pos1 = ps;

  };

  pos2(ps) {

    if (ps === undefined) return this._pos2;

    this._pos2 = ps;

  };

  Axy(ip) {

    if (ip === undefined) return this._Axy;

    return this._Axy[ip];

  };

  static colors(partId) {

    switch (partId) {

      case  1: return "dodgerblue";  // for tracks of muons
      case  2: return "#FF1111";     // for tracks of hadrons
      case  3: return "yellow";      // for tracks of e+/e-
      case  4: return "white";       // for highly ionizing tracks
      case  5: return "white";       // for back highly ionizing tracks
      case  6: return "springgreen"; // for ionizing tracks
      case  7: return "springgreen"; // for back ionizing tracks
      case  8: return "#FF1111";     // for tracks of tau leptons or charm particles
      case  9: return "aqua";         // for tracks of hadrons
      case 10: return "limegreen";    // for tracks of hadrons
      case 11: return "dodgerblue";   // for tracks of hadrons
      case 12: return "magenta";      // for tracks of hadrons
      case 13: return "lawngreen";    // for tracks of hadrons
      case 14: return "white";        // for tracks of hadrons
      case 15: return "gray";         // for tracks of hadrons
      case 16: return "orange";       // for tracks of hadrons or e+/e-
      case 17: return "yellow";       // for tracks of hadrons or e+/e-
      case 18: return "deeppink";     // for tracks e+/e-
      case 19: return "antiquewhite"; // for tracks e+/e-
      case 20: return "#FF1111";      // for tracks of hadrons

      default: return "black";      // for other tracks (not used!)
    }

  };

};
//------------------------------------------------------------------------------
