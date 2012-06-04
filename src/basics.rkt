#lang racket

;basic procedures, contracts, and the like for fulmar

;basic helper functions

(define pred/c (-> any/c boolean?))
(provide pred/c)

;flattens any list
(define/contract (flatten* . g)
  (->* () #:rest (listof any/c) (listof any/c))
  (flatten g))
(provide flatten*)

;predicate for a non-empty list
(define/contract (non-empty-list? g)
  pred/c
  (and (list? g)
       (not (null? g))))
(provide non-empty-list?)

;predicate for the or of given predicates
(define/contract (or? . preds)
  (->* () #:rest (listof pred/c) pred/c)
  (λ (g)
    (ormap (λ (pred?) (pred? g))
           preds)))
(provide or?)

;predicate for the and of given predicates
(define/contract (and? . preds)
  (->* () #:rest (listof pred/c) pred/c)
  (λ (g)
    (andmap (λ (pred?) (pred? g))
           preds)))
(provide and?)

;predicate for list of at least a given length and each element matches a given predicate
(define/contract list-of?
  (case-> (-> pred/c exact-nonnegative-integer? (->* () #:rest (listof any/c) boolean?))
          (-> pred/c exact-nonnegative-integer? #:rest (listof any/c) boolean?))
  (case-lambda [(pred? len)
                (λ g
                  (let ([lst (flatten* g)])
                    (if (null? lst)
                        (= 0 len)
                        (list-of? pred? len lst))))]
               [(pred? len . g)
                (let ([lst (flatten* g)])
                  (and (<= len (length lst))
                       (andmap pred? lst)))]))
;(define/contract (list-of? pred? len . g)
;  (->* (pred/c exact-nonnegative-integer?) #:rest (listof any/c) boolean?)
;  (let ([lst (flatten* g)])
;    (and (<= len (length lst))
;         (andmap pred? lst))))
(provide list-of?)

;predicates

;predicate for indent/position
(define/contract (indent? g)
  pred/c
  (exact-nonnegative-integer? g))
(provide indent?)

;predicate for optional indent/position
(define/contract (optional-indent? g)
  pred/c
  ((or? not
        indent?) g))
(provide optional-indent?)

;predicate for line length value
(define/contract (line-length? g)
  pred/c
  (exact-positive-integer? g))
(provide line-length?)