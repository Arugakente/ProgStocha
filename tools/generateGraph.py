import pandas as pd
import matplotlib.pyplot as plt

def generateGraph(pathFile, titre):
    df = pd.read_csv(pathFile)

    fig, ax = plt.subplots()
    ax.set_xlim(df['temperature'].iloc[0], df['temperature'].iloc[-1])

    ax.scatter(df['temperature'], df['current'], color='#4fadcf', label='energie courante')
    ax.plot(df['temperature'], df['temporary_best'], color = '#ff9c1d', label='reference actuelle')
    ax.plot(df['temperature'], df['overall_best'], color = '#db525a', label='meilleur global')
    ax.legend()
    plt.title(titre)
    plt.xlabel('temperature')
    plt.savefig(titre + '.png')


print("basic_glouton")
generateGraph('../recuitSimule/basic_glouton.csv', 'Glouton basique')
print("basic_rand")
generateGraph('../recuitSimule/basic_rand.csv', 'Random basique')
print("multi_glouton")
generateGraph('../recuitSimule/multi_glouton.csv', 'Glouton multiple')
print("multi_rand")
generateGraph('../recuitSimule/multi_rand.csv', 'Random multiple')
print("stack_glouton")
generateGraph('../recuitSimule/stack_glouton.csv', 'Glouton stack')
print("stack_rand")
generateGraph('../recuitSimule/stack_rand.csv', 'Random stack')