import http.server
import socketserver


class TurboServer(http.server.SimpleHTTPRequestHandler):
    paths = {
        # General purpose routes
        "/": {
            "content-type": "html",
            "filename": "src/views/index.html",
            "response_code": 200
        },
        "/addCustomer": {
            "content-type": "html",
            "filename": "src/views/addCustomer.html",
            "response_code": 200
        },
        "/identifyCustomer": {
            "content-type": "html",
            "filename": "src/views/identifyCustomer.html",
            "response_code": 200
        },
        "/saveCustomer": {
            "content-type": "html",
            "filename": "src/views/saveCustomer.html",
            "response_code": 200
        },
        "/showCustomer": {
            "content-type": "html",
            "filename": "src/views/showCustomer.html",
            "response_code": 200
        },
        "/Turbo.asm.js": {
            "content-type": "application/javascript",
            "filename": "bin/Turbo.asm.js",
            "response_code": 200
        },
        "/Turbo.asm.data": {
            "content-type": "application/javascript",
            "filename": "bin/Turbo.asm.data",
            "response_code": 200
        },
        "/Turbo.asm.wasm": {
            "content-type": "application/javascript",
            "filename": "bin/Turbo.asm.wasm",
            "response_code": 200
        },
        # Custom routes for tests
        "/Turbo.asm.js.mem": {
            "content-type": "application/javascript",
            "filename": "bin/Turbo.asm.js.mem",
            "response_code": 200
        },
        "/Turbo.test.data": {
            "content-type": "application/javascript",
            "filename": "bin/Turbo.test.data",
            "response_code": 200
        },
        "/Turbo.test.js": {
            "content-type": "application/javascript",
            "filename": "bin/Turbo.test.js",
            "response_code": 200
        },
        "/test": {
            "content-type": "html",
            "filename": "src/views/test.html",
            "response_code": 200
        }
    }

    def do_GET(self):
        raw_path = self.path.split("?")[0]
        if raw_path in TurboServer.paths:
            route_options = TurboServer.paths[raw_path]

            self.send_response(route_options["response_code"])
            self.send_header('content-type', route_options["content-type"])
            self.end_headers()

            file_content = open(route_options["filename"], "rb").read()
            self.wfile.write(file_content)
        else:
            super().do_GET()


def run():
    print("Starting server at: http://localhost:8080")
    httpd = socketserver.TCPServer(('localhost', 8080), TurboServer)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        httpd.server_close()


if __name__ == "__main__":
    run()
