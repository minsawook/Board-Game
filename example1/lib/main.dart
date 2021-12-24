import 'package:example1/PlayerThree.dart';
import 'package:example1/playerTwo.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'PlayerOne.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(MaterialApp(title: 'Board_Game', home: MyApp()));
}

class MyApp extends StatelessWidget {
  FirebaseFirestore firestore = FirebaseFirestore.instance;

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        title: '플레이어 선택',
        debugShowCheckedModeBanner: false,
        home: Scaffold(
          appBar: AppBar(
            title: Text('플레이어를 선택하세요'),
            centerTitle: true,
            elevation: 0.0,
            backgroundColor: Colors.black,
          ),
          body: Center(
              child: Container(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: <Widget>[
                Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: <Widget>[
                    ElevatedButton(
                      child: Text('player 1'),
                      onPressed: () async {
                        try {
                          await firestore
                              .collection('Players')
                              .doc('player1')
                              .set({"player": 1});
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) =>
                                      PlayerOne(appbarTitle: 'Player 1')));
                        } catch (e) {
                          print('You got an error! $e');
                        }
                      },
                      style: ButtonStyle(
                          backgroundColor: MaterialStateProperty.all<Color>(
                              Colors.red[300])),
                    ),
                    ElevatedButton(
                      child: Text('player 2'),
                      onPressed: () async {
                        try {
                          await firestore
                              .collection('Players')
                              .doc('player2')
                              .set({"player": 2});
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) =>
                                      PlayerTwo(appbarTitle: 'Player 2')));
                        } catch (e) {
                          print('You got an error! $e');
                        }
                      },
                      style: ButtonStyle(
                          backgroundColor: MaterialStateProperty.all<Color>(
                              Colors.yellow[300])),
                    ),
                    ElevatedButton(
                      child: Text('player 3'),
                      onPressed: () async {
                        try {
                          await firestore
                              .collection('Players')
                              .doc('player3')
                              .set({"player": 3});
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) =>
                                      PlayerThree(appbarTitle: 'Player 3')));
                        } catch (e) {
                          print('You got an error! $e');
                        }
                      },
                      style: ButtonStyle(
                          backgroundColor: MaterialStateProperty.all<Color>(
                              Colors.green[300])),
                    ),
                  ],
                ),
              ],
            ),
          )),
        ));
  }
}
