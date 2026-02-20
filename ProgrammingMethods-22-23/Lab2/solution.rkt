; Wojciech Kieloch 339952 pracownia 2 MP 2023

#lang racket/base
(require data/heap)
(require racket/match)
(require racket/contract)
(require racket/math)

(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))

;; Automatyczna implementacja:
; wire-value
; sim-time

; struktura wydarzenia (akcja, moment (czas) wykonania)
(struct event (action time) #:transparent)

(define (make-event act time) (event act time))

(define (eventCmp e1 e2) (<= (event-time e1) (event-time e2)))

(struct wire (sim [value  #:mutable] [events  #:mutable]) #:transparent)

(define (make-wire sim) (wire sim #f null))

(struct sim ([time #:mutable] [events  #:mutable]) #:transparent)

(define (make-sim)
  (sim 0 (make-heap eventCmp)))

(define (sim-add-action! sim delay action) (heap-add! (sim-events sim) (make-event action (+ (sim-time sim) delay))))

;; TIME

(define (sim-wait! sim delta)
  (executeTo sim (+ (sim-time sim) delta)))

; Wykonuje wydarzenia z symulacji do zadanej pory.
(define (executeTo sim endTime)
  (let ([acts (sim-events sim)])
  (cond [(= (heap-count acts) 0) (set-sim-time! sim endTime)]
        [(>= endTime (event-time (heap-min acts)))
         (let ([crEvent (heap-min acts)])
           (heap-remove-min! acts)
           (set-sim-time! sim (event-time crEvent))
           ((event-action crEvent))
           (executeTo sim endTime))]
        [else (set-sim-time! sim endTime)]))) ; jeżeli w zakresie czasowym nie ma już wydarzeń do wykonania.

; Wywołuje wszystkie funkcje bezargumentowe z listy funkcji.
(define (call-each funLst)
  (cond [(null? funLst) (void)]
        [else (begin ((car funLst)) (call-each (cdr funLst)))]))

(define (wire-set! wir new-value)
  (if (eq? (wire-value wir) new-value) (void) ; aktualizujemy, tylko jeżeli zachodzi zmiana wartości.
      (begin
        (set-wire-value! wir new-value)
        (call-each (wire-events wir))
        (void))))

(define (wire-add-action! wir action)
  (set-wire-events! wir (cons action (wire-events wir))))

(define (wire-on-change! wir action) (begin (wire-add-action! wir action) (action)))

(define normalDelay 1)
(define xorDelay 2)

(define (xor a b) (and (or a b) (not (and a b))))
(define (nand a b) (not (and a b)))
(define (nor a b) (not (or a b)))

; Logika odpowiadająca za bramki z jednym wejściem.
(define (oneInp-gate-logic output a fun delay)
  (wire-on-change! a (lambda () (sim-add-action!
                                 (wire-sim output)
                                 delay
                                 (lambda () (wire-set! output (fun (wire-value a))))))))

; Logika odpowiadająca za bramki z dwoma wejściami.
(define (twoInp-gate-logic output a b fun delay)
  (define (updateOutput)
      (sim-add-action!
       (wire-sim output)
       delay
       (lambda () (wire-set! output (fun (wire-value a) (wire-value b))))))
  (wire-on-change! b updateOutput)
  (wire-on-change! a updateOutput))

;; GATES

(define (gate-not output a)
   (oneInp-gate-logic output a (lambda (a) (not a)) normalDelay))
  
(define (gate-and output a b)
  (twoInp-gate-logic output a b (lambda (a b) (and a b)) normalDelay))

(define (gate-nand output a b)
  (twoInp-gate-logic output a b (lambda (a b) (nand a b)) normalDelay))

(define (gate-or output a b)
  (twoInp-gate-logic output a b (lambda (a b) (or a b)) normalDelay))

(define (gate-nor output a b)
  (twoInp-gate-logic output a b (lambda (a b) (nor a b)) normalDelay))

(define (gate-xor output a b)
  (twoInp-gate-logic output a b (lambda (a b) (xor a b)) xorDelay))

; WIRES

(define (wire-not inp)
  (let ([newWire (make-wire (wire-sim inp))])
    (oneInp-gate-logic newWire inp (lambda (a) (not a)) normalDelay)
  newWire))

(define (wire-and a b)
  (let ([newWire (make-wire (wire-sim a))])
    (twoInp-gate-logic newWire a b (lambda (a b) (and a b)) normalDelay)
  newWire))

(define (wire-nand a b)
  (let ([newWire (make-wire (wire-sim a))])
    (twoInp-gate-logic newWire a b (lambda (a b) (nand a b)) normalDelay)
  newWire))

(define (wire-or a b)
  (let ([newWire (make-wire (wire-sim a))])
    (twoInp-gate-logic newWire a b (lambda (a b) (or a b)) normalDelay)
  newWire))

(define (wire-nor a b)
  (let ([newWire (make-wire (wire-sim a))])
    (twoInp-gate-logic newWire a b (lambda (a b) (nor a b)) normalDelay)
  newWire))

(define (wire-xor a b)
  (let ([newWire (make-wire (wire-sim a))])
    (twoInp-gate-logic newWire a b (lambda (a b) (xor a b)) xorDelay)
  newWire))

;; PROVIDED

; flip-flop

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

; buses

(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))