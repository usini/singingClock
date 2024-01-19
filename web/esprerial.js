
// Based on the documentation from https://web.dev/serial/

class LineBreakTransformer {
    constructor(endline) {
      this.container = '';
      this.endline = endline;
    }
  
    transform(chunk, controller) {
      this.container += chunk;
      const lines = this.container.split(this.endline);
      this.container = lines.pop();
      lines.forEach(line => controller.enqueue(line));
    }
  
    flush(controller) {
      controller.enqueue(this.container);
    }
  }
  
  class Esprerial {
    constructor(baudrate = 115200, endline = "\r\n") {
      this.baudrate = baudrate;
      this.endline = endline;
      this.active = false;
      this.port = null
      this.inputDone = null;
      this.inputStream = null;
      this.writer = null;
      this.reader = null;
    }
  
    // Begin Serial Communication
    async begin() {
      if (navigator.serial) {
        try {
          //Request Serial Port
          this.port = await navigator.serial.requestPort();
          await this.port.open({ baudRate: this.baudrate });
  
          let decoder = new TextDecoderStream();
          this.inputDone = this.port.readable.pipeTo(decoder.writable);
          this.inputStream = decoder.readable.pipeThrough(
            new TransformStream(new LineBreakTransformer(this.endline))
          );
  
          const textEncoder = new TextEncoderStream();
          const writableStreamClosed = textEncoder.readable.pipeTo(this.port.writable);
          this.writer = textEncoder.writable.getWriter();
          this.reader = this.inputStream.getReader();
          this.startCallback();
          this.read();
        } catch (error) {
          this.errorCallback(error)
        }
      } else {
        this.errorCallback("Web Serial not supported");
      }
    }
  
    // Manage Read Message
    async read() {
      this.active = true;
      let i = 0;
      while (true) {
        const { value, done } = await this.reader.read();
        if (value) {
          this.readCallback(value);
          if (done) {
            reader.releaseLock();
            break;
          }
        }
      }
    }

    async close() {
      this.port.forget();
    }

    // When the navigator received a message
    readCallback(value){
      console.log(value);
    }
  
    // When an Error occurred
    errorCallback(error){
      console.log(error);
    }
  
    // When a Serial Communication Start
    startCallback(){
      console.log("Started Web Serial");
    }
  
    // Set Error Callback
    setError(errorCallback) {
      this.errorCallback = errorCallback;
    }
  
    // Set Start Callback
    setStart(startCallback) {
      this.startCallback = startCallback;
    }
  
    // Set Read Callback
    setRead(readCallback) {
      this.readCallback = readCallback;
    }
  
    // Send to a message 
    async write(text) {
      this.writer.write(text + this.endline);
    }
  }