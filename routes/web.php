<?php

use Illuminate\Support\Facades\Route;
use App\Events\testEvent;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', [\App\Http\Controllers\RoomController::class, 'index']);

Route::post('/update', [\App\Http\Controllers\RoomController::class, 'update']);

Route::get('/addRoom', [\App\Http\Controllers\RoomController::class, 'create']);

Route::post('/room', [\App\Http\Controllers\RoomController::class, 'store']);
<<<<<<< HEAD

Route::get('/Nils', function() {
    echo "Hallo Nils";
});
// Test
=======
// Route::get('/addRoom/{roomName}/{number}', [\App\Http\Controllers\RoomController::class, 'add']);
>>>>>>> 92998db1716f0ad4748f8a2bbb28f78d6534d037
