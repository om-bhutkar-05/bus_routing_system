import csv
import json

def convert_csv_to_json(input_file, output_file):
    connections = []
    places = {}
    place_id_counter = 1
    
    with open(input_file, 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        
        for row in reader:
            route_description = row["Route Description"]
            route_split = route_description.split(" To ")
            if len(route_split) != 2:
                print(f"Skipping row with invalid Route Description: {route_description}")
                continue
            
            source = route_split[0].strip()
            destination = route_split[1].strip()
            kilometer = row["Kilometer"]
            
            if source not in places:
                places[source] = str(place_id_counter)
                place_id_counter += 1
            if destination not in places:
                places[destination] = str(place_id_counter)
                place_id_counter += 1
            
            connection = {
                "source": places[source],
                "destination": places[destination],
                "weight": kilometer
            }
            connections.append(connection)
    
    output_data = {
        "places": [{"id": place_id, "place_name": place_name} for place_name, place_id in places.items()],
        "connections": connections
    }
    
    with open(output_file, 'w') as jsonfile:
        json.dump(output_data, jsonfile, indent=2)

convert_csv_to_json("assets/bus_routes.csv", "assets/routes.json")
