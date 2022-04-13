<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use DB;

class RoomController extends Controller
{
    public function index(){
        return view('dashboard', [
            'room' => \App\Models\Room::all()
        ]);
    }

    public function create(){
        return view('addRoom', [
            'rooms' => \App\Models\Room::all()
        ]);
    }

    public function update(Request $request, \App\Models\Room $room) {
        try{
            $room::where('roomName', $request->roomName)
            ->update(['people' => $request->people]);
            return redirect('/');
        } catch(Exception $e){
            return redirect('/');
        }
    }

    public function store(Request $request, \App\Models\Room $room){
        $room = \App\Models\Room::all()->where('id', $request->input('id'))->first();
        $room->roomName = $request->input('roomName');
        $room->people = $request->input('people');

        try{
            $room->save();
            return redirect('/');
        } catch(Exception $e){
            return redirect('/addRoom');
        }
    }
}
