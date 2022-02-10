#ifndef _HTML_h
#define _HTML_h_

#include <Arduino.h>

const char css_head[] PROGMEM = R"rawliteral(
<html>
<head>
    <style>
        body {
            font-family: "Helvetica";
        }
        button {
            background-color: #005F41;
            color: white;
            margin: 10px;
            padding: 15px 32px;
            text-align: center;
            font-size: 16px;
            display: block;
            border-radius: 4px;
            width: 150px;
            text-decoration: none;
            transition: 0.3s;
        }
        button:hover {
            background-color: #3d8b40;
        }
        input[type=text] {
            width: 30%;
            height: 40px;
            margin: 10px;
            font-size: large;
            border: 2px solid black;
            border-radius: 4px;
        }
        input:invalid {
            border: 2px solid red;
            border-radius: 4px;
        }
        label {
            font-size: 20px;
        }
        select {
            margin: 20px;
            font-size: 20px;
        }
        table {
            border-collapse: collapse;
            border: 1px solid black;
        }
        th, td {
            padding: 8px;
            text-align: left;
            border: 1px solid black;
}
    </style>
</head>
<body>
<center>
)rawliteral";

#endif
