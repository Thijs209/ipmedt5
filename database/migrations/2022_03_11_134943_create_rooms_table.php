<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateRoomsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('rooms', function (Blueprint $table) {
            $table->string('id');
            $table->primary('id');
            $table->string('roomName')->default('nieuwe kamer');
            $table->integer('domoticz_idx')->default(0);
            $table->unique("domoticz_idx");
            $table->integer('people')->default(0);
            $table->timestamps();
            $table->boolean('light_status')->default(0);
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('rooms');
    }
}
