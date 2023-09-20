import requests
import json

API_KEY = "f721b437a965b0a0b0bf8bf406432e74"  # Replace with your OpenWeatherMap API key
LATITUDE = "43.335209"  # Replace with your location's latitude
LONGITUDE = "-79.895393"  # Replace with your location's longitude

def get_rainfall_forecast(api_key, latitude, longitude):
    url = f"https://api.openweathermap.org/data/2.5/forecast?lat={latitude}&lon={longitude}&appid={api_key}"

    response = requests.get(url)
    data = json.loads(response.text)

    rainfall_forecast = []
    for forecast in data["list"]:
        rainfall = forecast.get("rain", {}).get("3h", 0)
        rainfall_forecast.append(rainfall)

    return rainfall_forecast


rainfall_forecast = get_rainfall_forecast(API_KEY, LATITUDE, LONGITUDE)
print("Rainfall forecast for the next 5 days, in 3h increments:")
for i in range(len(rainfall_forecast)):
    print("Hour " + str(i*3+3) +": " + str(rainfall_forecast[i]) + " mm")
