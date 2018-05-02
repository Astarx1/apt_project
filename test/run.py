import requests
import json

print("Player 1 creation ...")
r = requests.post("http://127.0.0.1:9080/player")
j = json.loads(r.text)
print(r)
i1 = str(j["id_player"])

print("Player 1 read ...")
r = requests.get("http://127.0.0.1:9080/player/" + i1)
j = json.loads(r.text)
print(r)

print("Player 2 creation ...")
r = requests.post("http://127.0.0.1:9080/player")
j = json.loads(r.text)
print(r)
i2 = str(j["id_player"])

print("Game post without winner...")
js = {
    "id_player_1": int(i1),
    "id_player_2": int(i2),
    "moves": "none"
}
r = requests.post("http://127.0.0.1:9080/game", json=json.dumps(js))
print(r)

print("Game post with winner...")
js = {
    "id_player_1": int(i1),
    "id_player_2": int(i2),
    "moves": "none",
    "winner": 1,
}
r = requests.post("http://127.0.0.1:9080/game", json=json.dumps(js))
print(r)

js = {
    "id_player_1": int(i1),
    "id_player_2": int(i2),
    "moves": "none",
    "winner": 1,
}
r = requests.post("http://127.0.0.1:9080/game", json=json.dumps(js))
print(r)


print("Game post with winner...")
js = {
    "id_player_1": int(i1),
    "id_player_2": int(i2),
    "moves": "none",
    "winner": 0,
}
r = requests.post("http://127.0.0.1:9080/game", json=json.dumps(js))
print(r)

print("Game post with winner...")
js = {
    "id_player_1": int(i1),
    "id_player_2": int(i2),
    "moves": "none",
    "winner": 0,
}
r = requests.post("http://127.0.0.1:9080/game", json=json.dumps(js))
print(r)

print("Read all players ...")
r = requests.get("http://127.0.0.1:9080/players")
print(r)
print(r.text)
ps = json.loads(r.text)

print("Clean all players ...")
for p in ps:
    r = requests.delete("http://127.0.0.1:9080/player/" + str(p["id_player"]))
    print(r)

print("Read all games ...")
r = requests.get("http://127.0.0.1:9080/games")
print(r)
gs = json.loads(r.text)

print("Clean all games ...")
for g in gs:
    r = requests.delete("http://127.0.0.1:9080/game/" + str(g["id_game"]))
    print(r)