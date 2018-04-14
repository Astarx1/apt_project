Models :
Game :
- id_game
- id_player_1
- level_1
- id_player_2
- level_1
- date_games
- plays

GameInformations
- id_info
- id_game
- type_info
- value_info

Player :
- id_player
- trivia_player

ConnectionInformation :
- id_player
- type_connection
- value_connection

To create tables :

CREATE TABLE GAMES(id_game INT PRIMARY KEY NOT NULL, id_player_1 INT NOT NULL, level_player_1 FLOAT NOT NULL, id_player_2 INT NOT NULL, level_player_2 FLOAT NOT NULL, date_game INT NOT NULL, moves TEXT);

CREATE TABLE GAMESINFOS(id_info INT PRIMARY KEY NOT NULL, id_game INT NOT NULL, type_info INT NOT NULL, value_info TEXT);

CREATE TABLE PLAYERS(id_player INT PRIMARY KEY NOT NULL, current_level FLOAT NOT NULL, trivia_player TEXT);

CREATE TABLE PLAYERSINFOS(id_info INT PRIMARY KEY NOT NULL, id_player INT NOT NULL, type_info INT NOT NULL, value_info TEXT);