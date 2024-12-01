import matplotlib.pyplot as plt

def read_coordinates(filename):
    x, y, z = [], [], []
    with open("coordinates.csv", "r") as file:
        for line in file:
            coords = line.strip().split(", ")
            x.append(float(coords[0]))
            y.append(float(coords[1]))
            z.append(float(coords[2]))
    return x, y, z

def plot_coordinates(x, y):
    plt.figure(figsize=(10, 10))
    plt.scatter(x, y, c='blue', label='Coordinates', s=1)
    plt.xlabel('X')
    plt.xlabel('Y')
    plt.title('Coord visualisation')
    plt.legend()
    plt.grid()
    plt.savefig("plotXY.png")

if __name__ == "__main__":
    filename = "coordinates.csv"
    x, y, z = read_coordinates(filename)
    plot_coordinates(x, y)
