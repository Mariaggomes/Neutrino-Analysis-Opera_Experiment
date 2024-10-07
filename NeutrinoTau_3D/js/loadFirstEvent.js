let value = document.querySelector('#body-display3d').dataset.eventId;

let evID = +value;

let evIndex = -1;

display3d.evIndex(1);

evID = display3d.evList(1)[1];

display3d.evIndexMax(display3d.evList(1).length - 1);

changeScrLoadEvent(evID);

//-------------------------------------------------------------------------------

function changeScrLoadEvent(evID) {
  // It is assumed here that the evID has been already checked!

  let scrLoadEvent = document.createElement("script");

  scrLoadEvent.src = "js/nuEventsData/nuTau/loadEvent" + evID + ".js";

  scrLoadEvent.innerHTML = null;
  scrLoadEvent.id = "script-LoadEvent";

  let divScrLoadEvent = document.getElementById("div-ScrLoadEvent");

  divScrLoadEvent.innerHTML = "";
  divScrLoadEvent.appendChild(scrLoadEvent);
}
//------------------------------------------------------------------------------
