Endpoints :
- /player :
	- POST :
		- {"name": str} -> {"id":int}

- /player?id={int}
	- GET :
		- {"id": int, name": str, "level": float}

- /player?name={str}
	- GET
		- {"id": int, name": str, "level": float}

- /game
	- POST : 
		- {"date": int, "id_player1": int, "id_player_2": int, "result": str, "moves": str} -> {"id": int}

- /game?id={int}
	- GET

- /games?name={str}

?page={int}&perpage={int}