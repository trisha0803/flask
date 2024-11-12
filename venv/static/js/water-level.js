// Call the function on page load with an initial value
window.onload = function() {
    updateProgress(0); // Set this to your initial value
    fetchHumidity();
    setInterval(() => {
        fetchHumidity();
    }, 3000); // 3000 milliseconds = 3 seconds
};

function updateProgress(value) {
    const progressText = document.querySelector('.progress-text');
    const progressBar = document.querySelector('.progress-bar');
    const waterData = document.querySelector('.water-data');

    // Set the width of the progress bar
    progressBar.style.width = value + '%';
    progressBar.setAttribute('aria-valuenow', value);

    // Determine text color based on value
    if (value <= 47) {
        progressText.className = 'progress-text text-primary';
    } else if (value >= 52){
        progressText.className = 'progress-text'; // Default, no special class
        progressText.style.color = 'white'; // Set to white if above 50%
    }
    else if (value == 48) {
        progressText.style.background = 'linear-gradient(to bottom, blue 70%, white 30%)'; // Use 'to right' for horizontal gradient
        progressText.style.color = 'transparent'; // Make text color transparent to show gradient
        progressText.style.backgroundClip = 'text'; // Use camelCase for 'background-clip'
        progressText.style.webkitBackgroundClip = 'text'; // Add for WebKit browsers
    } else {
        progressText.className = 'progress-text text-gradient';
    }

    // Update text value
    progressText.textContent = value + "cm";
    waterData.textContent = value + "cm";
    
}