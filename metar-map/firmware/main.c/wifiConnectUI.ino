
const char wifiCredentialsPage[] PROGMEM = R"htmlcode(
    <html>

<head>
    <title>METAR Map</title>
    <style type="text/css">
        .content {
            min-height: 100%;
            display: grid;
            grid-template-rows: 100px auto 50px;
            grid-template-areas:
                "header"
                "content"
                "footer";
            justify-items: center;
            align-items: center;
        }

        .header {
            grid-area: header;
        }

        .header h1,
        .header h4 {
            text-align: center;
        }

        .connect-form {
            grid-area: content;
        }

        .content,
        .header,
        .footer {
            flex: 1;
            justify-content: center;
            align-items: center;
        }

        .footer {
            grid-area: footer;
            font-size: 8px;
        }
    </style>
</head>

<body>
    <section class="content">
        <section class="header">
            <h1>METAR Map Project</h1>
            <h4>Connect to WiFi</h4>
        </section>

        <section class="connect-form">
            <form action="/connect" method="POST">
                <div>
                    <label for="network-ssid">WiFi network SSID:</label>
                    <input type="text" name="network-ssid">
                </div>

                <div>
                    <label for="wifi-password">WiFi password:</label>
                    <input type="password" name="wifi-password">
                </div>

                <input type="submit" value="Connect">
            </form>
        </section>

        <section class="footer">
            Created by Andrew Kovalenko&nbsp;&copy;&nbsp;<span id="year"></span>
        </section>
    </section>
    <script type="text/javascript">
        document.getElementById("year").textContent = new Date().getFullYear();
    </script>
</body>

</html>
)htmlcode";