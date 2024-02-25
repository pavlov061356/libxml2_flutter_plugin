import 'dart:developer';

import 'package:flutter/material.dart';
import 'dart:async';

import 'package:libxml2_flutter_plugin/libxml2_flutter_plugin.dart'
    as libxml2_flutter_plugin;

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  // late int sumResult;
  // late Future<int> sumAsyncResult;

  @override
  void initState() {
    super.initState();

    log(
      libxml2_flutter_plugin.XmlValidatorPlugin.instance!.validateXml(
            '../test_data/successful/test.xml',
            '../test_data/successful/test.xsd',
          ) ??
          'xml is valid',
    );

    log(
      libxml2_flutter_plugin.XmlValidatorPlugin.instance!.validateXml(
            '../test_data/wrong/test.xml',
            '../test_data/wrong/test.xsd',
          ) ??
          'xml is valid',
    );

    // sumResult = libxml2_flutter_plugin.sum(1, 2);
    // sumAsyncResult = libxml2_flutter_plugin.sumAsync(3, 4);
  }

  @override
  Widget build(BuildContext context) {
    const textStyle = TextStyle(fontSize: 25);
    const spacerSmall = SizedBox(height: 10);
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Native Packages'),
        ),
        body: SingleChildScrollView(
          child: Container(
            padding: const EdgeInsets.all(10),
            child: const Column(
              children: [
                Text(
                  'This calls a native function through FFI that is shipped as source in the package. '
                  'The native code is built as part of the Flutter Runner build.',
                  style: textStyle,
                  textAlign: TextAlign.center,
                ),
                spacerSmall,
              ],
            ),
          ),
        ),
      ),
    );
  }
}
