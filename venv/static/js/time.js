function updateTime() {
    const timeElement = document.getElementById('current-time');
    const now = new Date();
    
    // Get hours, minutes, and seconds
    let hours = now.getHours();
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    // Determine AM or PM suffix
    const ampm = hours >= 12 ? 'PM' : 'AM';
    
    // Convert 24-hour format to 12-hour format
    hours = hours % 12;
    hours = hours ? hours : 12; // If hour is 0 (midnight), display as 12

    // Format hours with leading zero if needed
    const formattedHours = String(hours).padStart(2, '0');
    
    // Final time format
    const currentTime = `${formattedHours}:${minutes}:${seconds} ${ampm}`;
    
    // Display the current time
    timeElement.innerText = currentTime;

    // Save the current time to sessionStorage so it persists during navigation
    sessionStorage.setItem('savedTime', currentTime);
}

// Update the time every second
setInterval(updateTime, 1000);

// Initialize the time when the page loads
document.addEventListener('DOMContentLoaded', function () {
    const savedTime = sessionStorage.getItem('savedTime');
    
    // If there's a saved time, display it when the page loads
    if (savedTime) {
        document.getElementById('current-time').innerText = savedTime;
    }

    // Call the updateTime function to start the clock
    updateTime();
});
