<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class RoomController extends Controller
{
    public function show(){
        return view('dashboard', [
            'room' => \App\Models\Room::first()
        ]);
     }
}