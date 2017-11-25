// Displays a loading message while the page isn't loaded
// then, runs the code in main once it is loaded.
displayLoadingOverlay();
let loading = function() {
    if (window.isDbLoaded) { 
        main();
        hideLoadingOverlay();
    } else {
        setTimeout(loading, 0);
    }
};
setTimeout(loading, 0);

// Display loading message.
function displayLoadingOverlay() {
    document.getElementById("loading-overlay").style.display = "block";
    document.getElementById("content").style.display = "none";
}

function hideLoadingOverlay() {
    document.getElementById("loading-overlay").style.display = "none";
    document.getElementById("content").style.display = "block";
}
