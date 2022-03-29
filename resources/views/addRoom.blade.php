<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
</head>
<body>
    <form action="/room" method="POST">
        @csrf
        <label for="roomNameField">Kamer Naam</label><br>
        <input id="roomNameField" name="roomName" type="text"><br>
    
        <label for="numberPeopleField">Hoeval mensen zijn er in de kamer?</label><br>
        <input id="numberPeopleField" name="people" type="number" value="0"><br>

        <input type="submit" value="Submit" id="submit">
    </form>
</body>
</html>