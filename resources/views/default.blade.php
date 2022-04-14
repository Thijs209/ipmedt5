<!DOCTYPE html>
<html lang="nl">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="css/main.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Poiret+One&display=swap" rel="stylesheet">
    <title>@yield('title')</title>
    @yield('script')
</head>
<body>
    <header>
        <a href='/'><h1>Lightly</h1></a>
        <a href='/addRoom' class='header-add'>Kamer Wijzigen</a>
    </header>
        @yield('content')
</body>
</html>