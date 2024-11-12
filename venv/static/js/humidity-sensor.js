function fetchHumidity() {
    fetch('/api/humidity')
        .then(response => response.json())
        .then(data => {
            // Update the HTML with the received humidity data
            document.getElementById('humidity-display').innerText = data.humidity + '%';

            distance = data.distance;
            updateProgress(distance);
        })
        .catch(error => console.error('Error fetching humidity:', error));
}
