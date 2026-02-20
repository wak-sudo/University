for i in {1..100}; do
    python3 zad3.py "tests/in/graph$i.txt" > "tests/out/graph$i.txt"
    echo "Zaproksymowano: tests/in/graph$i.txt"
done
echo "Zakończono generowanie plików."