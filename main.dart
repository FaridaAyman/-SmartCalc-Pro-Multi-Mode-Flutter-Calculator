import 'package:flutter/material.dart';

void main() {
  runApp(UserInfoApp());
}

class UserInfoApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: UserInfoScreen(),
    );
  }
}

class UserInfoScreen extends StatefulWidget {
  @override
  _UserInfoScreenState createState() => _UserInfoScreenState();
}

class _UserInfoScreenState extends State<UserInfoScreen> {
  final TextEditingController nameController = TextEditingController();
  final TextEditingController ageController = TextEditingController();
  String userInfo = '';
  Color backgroundColor = Colors.white;
  String errorMessage = '';

  void submitData() {
    setState(() {
      String name = nameController.text;
      String ageText = ageController.text;

      if (name.isEmpty || ageText.isEmpty) {
        errorMessage = "Please enter both name and age!";
        userInfo = '';
        backgroundColor = Colors.white;
      } else {
        int age = int.tryParse(ageText) ?? 0;

        errorMessage = '';
        backgroundColor = (age < 18) ? Colors.blue : Colors.green;
        userInfo = 'Name: $name\nAge: $age';
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text("User Info Card")),
      body: Container(
        color: backgroundColor,
        padding: EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            CircleAvatar(
              radius: 50,
              backgroundImage: AssetImage("assets/profile.png"),
            ),
            SizedBox(height: 20),
            TextField(
              controller: nameController,
              decoration: InputDecoration(labelText: "Enter your name"),
            ),
            TextField(
              controller: ageController,
              decoration: InputDecoration(labelText: "Enter your age"),
              keyboardType: TextInputType.number,
            ),
            SizedBox(height: 20),
            ElevatedButton(
              onPressed: submitData,
              child: Text("Submit"),
            ),
            SizedBox(height: 20),
            userInfo.isNotEmpty
                ? Container(
              padding: EdgeInsets.all(16),
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(10),
                color: Colors.white,
              ),
              child: Text(
                userInfo,
                style: TextStyle(fontSize: 18, color: Colors.black),
                textAlign: TextAlign.center,
              ),
            )
                : Container(),
            errorMessage.isNotEmpty
                ? Text(
              errorMessage,
              style: TextStyle(color: Colors.red, fontSize: 16),
            )
                : Container(),
          ],
        ),
      ),
    );
  }
}
