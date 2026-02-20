for i in {1..100}; do
    python3 zad1.py "$i" > "tests/in/graph$i.txt"
    echo "Wygenerowano: tests/in/graph$i.txt"
done
echo "Zakończono generowanie plików."