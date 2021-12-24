import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

class PlayerOne extends StatefulWidget {
  final String appbarTitle;

  PlayerOne({Key key, @required this.appbarTitle}) : super(key: key);

  @override
  PlayerOneState createState() => PlayerOneState();
}

class PlayerOneState extends State<PlayerOne> {
  int a = 6;
  int dice;
  List<String> eventName = [
    '시작',
    '딱밤 맞기',
    '코끼리 코 3바퀴',
    '손목 맞기',
    '교수님 성대모사하기',
    '딱밤 때리기',
    '앉았다 일어나기 3번'
  ];

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: '플레이어 선택',
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: Text(widget.appbarTitle),
          centerTitle: true,
          elevation: 0.0,
          backgroundColor: Colors.red,
        ),
        body: Center(
            child: Container(
          margin: EdgeInsets.only(left: 30, top: 100, right: 30, bottom: 50),
          height: double.infinity,
          width: double.infinity,
          decoration: BoxDecoration(
            color: Colors.white,
            borderRadius: BorderRadius.only(
                topLeft: Radius.circular(10),
                topRight: Radius.circular(10),
                bottomLeft: Radius.circular(10),
                bottomRight: Radius.circular(10)),
            boxShadow: [
              BoxShadow(
                color: Colors.grey.withOpacity(0.5),
                spreadRadius: 5,
                blurRadius: 7,
                offset: Offset(0, 3), // changes position of shadow
              ),
            ],
          ),
          child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Text(dice.toString(), style: TextStyle(fontSize: 30.0)),
                Text(eventName[a], style: TextStyle(fontSize: 30.0))
              ]),
        )),
      ),
    );
  }

  // ignore: unused_element
  Future<void> initState() {
    super.initState();
    FirebaseFirestore.instance.collection('Events').snapshots().listen((data) {
      print(data.docs[0]['dicenum1']);
      setState(() {
        a = data.docs[0]['dicenum1'];
        dice = data.docs[0]['dicenum1'];
        print('a= $a');
      });
    });
  }
}