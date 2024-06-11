// Inizializza la variabile di controllo per il trascinamento
let isDraggable = false;

// Seleziona l'elemento div con id 'idFrame'
const div = document.getElementById('idFrame');

// Aggiunge un gestore per l'evento double-click sull'elemento div
div.ondblclick = function() {
    // Inverte lo stato di isDraggable
    isDraggable = !isDraggable;
    // Cambia il cursore del mouse in base allo stato di isDraggable
    div.style.cursor = isDraggable ? 'move' : 'pointer';
};

// Aggiunge un gestore per l'evento mousedown sull'elemento div
div.onmousedown = function(event) {
    // Se l'elemento non è trascinabile, esce dalla funzione
    if (!isDraggable) return;

    // Calcola gli offset tra la posizione del mouse e i bordi del div
    let shiftX = event.clientX - div.getBoundingClientRect().left;
    let shiftY = event.clientY - div.getBoundingClientRect().top;

    // Funzione per muovere l'elemento div alla nuova posizione del mouse
    function moveAt(pageX, pageY) {
        div.style.left = pageX - shiftX + 'px';
        div.style.top = pageY - shiftY + 'px';
    }

    // Funzione per gestire il movimento del mouse
    function onMouseMove(event) {
        moveAt(event.pageX, event.pageY);
    }

    // Aggiunge il listener per l'evento mousemove al documento
    document.addEventListener('mousemove', onMouseMove);

    // Aggiunge un gestore per l'evento mouseup sull'elemento div
    div.onmouseup = function() {
        // Rimuove il listener per l'evento mousemove
        document.removeEventListener('mousemove', onMouseMove);
        // Resetta il gestore per l'evento mouseup
        div.onmouseup = null;
    };
};

// Disabilita il comportamento predefinito di trascinamento del browser
div.ondragstart = function() {
    return false;
};
