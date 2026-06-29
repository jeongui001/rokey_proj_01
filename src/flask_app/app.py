from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
app.config['SECRET_KEY'] = 'lego-assembler'
socketio = SocketIO(app, cors_allowed_origins='*')


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/edit')
def edit():
    return render_template('edit.html')

@app.route('/progress')
def progress():
    return render_template('progress.html')


# ── Browser(/) → Bridge(/bridge) 중계 ──

@socketio.on('upload_image')
def on_upload_image(data):
    socketio.emit('upload_image', data, namespace='/bridge')

@socketio.on('update_grid')
def on_update_grid(data):
    socketio.emit('update_grid', data, namespace='/bridge')

@socketio.on('start_assembly')
def on_start_assembly(data):
    socketio.emit('start_assembly', data, namespace='/bridge')

@socketio.on('pause')
def on_pause():
    socketio.emit('pause', namespace='/bridge')

@socketio.on('resume')
def on_resume():
    socketio.emit('resume', namespace='/bridge')


# ── Bridge(/bridge) → Browser(/) 중계 ──

@socketio.on('analysis_result', namespace='/bridge')
def on_analysis_result(data):
    socketio.emit('analysis_result', data, namespace='/')

@socketio.on('grid_updated', namespace='/bridge')
def on_grid_updated(data):
    socketio.emit('grid_updated', data, namespace='/')

@socketio.on('block_plan', namespace='/bridge')
def on_block_plan(data):
    socketio.emit('block_plan', data, namespace='/')

@socketio.on('assembly_started', namespace='/bridge')
def on_assembly_started(data):
    socketio.emit('assembly_started', data, namespace='/')

@socketio.on('assembly_progress', namespace='/bridge')
def on_assembly_progress(data):
    socketio.emit('assembly_progress', data, namespace='/')

@socketio.on('assembly_done', namespace='/bridge')
def on_assembly_done(data):
    socketio.emit('assembly_done', data, namespace='/')

@socketio.on('assembly_error', namespace='/bridge')
def on_assembly_error(data):
    socketio.emit('assembly_error', data, namespace='/')

@socketio.on('system_log', namespace='/bridge')
def on_system_log(data):
    socketio.emit('system_log', data, namespace='/')


if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000, debug=True, allow_unsafe_werkzeug=True)
