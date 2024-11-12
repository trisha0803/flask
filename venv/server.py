from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

# This will store the latest humidity data
latest_data = {"humidity": 0}, {"distance": 0}


@app.route('/')
@app.route('/dashboard', methods=['GET'])
def dashboard():
    return render_template('dashboard.html')

@app.route('/dashboard/data', methods=['POST'])
def update_data():
    if request.is_json:
        data = request.get_json()  # Expecting JSON data
        print("Received JSON Data:", data)  # Debug print
        
        # Update the latest data
        global latest_data
        latest_data = data

        return jsonify({"status": "success"}), 200
    else:
        return jsonify({"error": "Unsupported Media Type"}), 415
    
@app.route('/api/humidity', methods=['GET'])
def get_humidity():
    return jsonify(latest_data)

# A route for 'records'
@app.route('/records')
def records():
    return render_template('records.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
