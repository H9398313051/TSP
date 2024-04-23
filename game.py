def tsp(c):
    minimum = float('inf')
    nearest_city = 999
    temp = 0
    for count in range(limit):
        if matrix[c][count] != 0 and visited_cities[count] == 0:
            if matrix[c][count] < minimum:
                minimum = matrix[count][0] + matrix[c][count]
            temp = matrix[c][count]
            nearest_city = count
    if minimum != float('inf'):
        global cost
        cost += temp
    return nearest_city

def minimum_cost(city):
    global cost
    visited_cities[city] = 1
    print(city + 1, end=" ")
    nearest_city = tsp(city)
    if nearest_city == 999:
        nearest_city = 0
        print(nearest_city + 1)
        cost += matrix[city][nearest_city]
        return
    minimum_cost(nearest_city)

if __name__ == "__main__":
    limit = int(input("Enter Total Number of Cities:\t"))
    matrix = []
    visited_cities = [0] * limit
    cost = 0

    print("\nEnter Cost Matrix")
    for i in range(limit):
        print(f"\nEnter {limit} Elements in Row[{i + 1}]")
        row = list(map(int, input().split()))
        matrix.append(row)

    print("\nEntered Cost Matrix")
    for row in matrix:
        print()
        print(" ".join(map(str, row)))

    print("\n\nPath:\t", end="")
    minimum_cost(0)
    print("\n\nMinimum Cost: \t")
    print(cost)


