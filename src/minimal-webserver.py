from time import sleep
from multiprocessing import Pipe

def frame_collector(clients):
  import io
  import socket
  SERV_IPV4, SERV_PORT = ('192.168.145.200', 8888)
  udpSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  udpSock.bind((SERV_IPV4,SERV_PORT))
  isWriting = False
  isConnected = False
  try:
    while 1:
      dataRecv, CLNT_ADDR = udpSock.recvfrom(65507)

      if not isConnected:
        if dataRecv == b'SYN\n':
          udpSock.sendto(b'ACK\n',CLNT_ADDR)
          udpSock.sendto(b'SOH\n',CLNT_ADDR)
          isConnected = True

      if not isWriting:
        if dataRecv[:2] == b'\xff\xd8': # Start of JPEG
          isWriting = True
          buf = io.BytesIO()

      if isWriting:
        buf.write(dataRecv)
        if dataRecv[-2:] == b'\xff\xd9': # End of JPEG
          isWriting = False
          buf.seek(0)
          frame = buf.read()
          d = dict(clients) # Make copy into local dict
          for handle, sender in d.items():
            try:
              sender.send(frame)
            except: # Client has gone away?
              del clients[handle]
  except KeyboardInterrupt: # ctrl-C
    pass

def flask_service(clients): # process 2
  from flask import Flask, Response
  app = Flask(__name__)

  def frame_consumer():
    receiver, sender = Pipe(False)
    clients[sender._handle] = sender
    while True:
      yield b'--frame\r\nContent-Type: image/jpeg\r\n\r\n' + receiver.recv() + b'\r\n'

  @app.route('/mjpeg')
  def mjpeg():
    return Response(frame_consumer(),mimetype='multipart/x-mixed-replace; boundary=frame')

  @app.route('/')
  def index():
    return """
    <body style="background: blue;">
      <div style="width: 800px; margin: 0px auto;">
        <img src="/mjpeg">
      </div>
    </body>
    """

  app.run(host='192.168.145.200', threaded=True)

if __name__ == '__main__':
  from multiprocessing import Process, Manager

  with Manager() as manager:
     clients = manager.dict()

     p1 = Process(target=frame_collector, args=(clients,))
     p2 = Process(target=flask_service, args=(clients,))
     p1.start()
     p2.start()

     try:
       p2.join() # block while flask_service is running
     except: # ctrl-C
       p1.terminate()
       p2.terminate()
     finally:
       print('Ending up.')