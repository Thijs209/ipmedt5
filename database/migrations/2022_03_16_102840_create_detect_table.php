<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateDetectTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('detect', function (Blueprint $table) {
            $table->string("room_name");
            $table->timestamps();
            $table->id("roomID");
            $table->string("gate_1")->default("false");
            $table->string("gate_2")->default("false");
            $table->timestamp('gate_1_timestamp')->nullable();
            $table->timestamp('gate_2_timestamp')->nullable();
        });
    }
    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('detect');
    }
}
