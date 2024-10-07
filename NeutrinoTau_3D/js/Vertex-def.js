class Vertex {

  constructor(pos, posGlob) {

    this._pos = pos;         // [posX, posY, posZ] Position in the OPERA brick system of reference (in micrometers)

    this._posGlob = posGlob; // [posGlobX, posGlobY, posGlobZ] Position in the OPERA detector system of reference (in cm)

  };

  pos(ps) {

    if (ps === undefined) return this._pos;

    this._pos = ps;

  };

  posGlob(ps) {

    if (ps === undefined) return this._posGlob;

    this._posGlob = ps;

  };

  static colorFor3D() { return "gold"; };

};
