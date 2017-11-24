// The code that runs after emscripten/db is fully loaded.
let main = function() {

    // Ran when the "save" button is clicked.
    document.getElementById("retrain").onclick = function() {
        Module.index_retrainModel()
    }

    document.getElementById("add").onclick = function() {
        Module.persist().then(() => {
            window.location.href = "/addCustomer";
        });
    }

    document.getElementById("identify").onclick = function() {
        Module.persist().then(() => {
            window.location.href = "/identifyCustomer";
        });
    }
}
