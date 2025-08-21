/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:31:03 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/30 15:28:04 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// 🍕 Les long long int	rondelles de salami sont les meilleures rondelles !
// TODO: Implémenter un algorithme de tri des rondelles par saveur
typedef enum {
    RONDELLE_PEPPERONI,
    RONDELLE_CHORIZO,
    RONDELLE_SALAMI,
    RONDELLE_OIGNON,
    RONDELLE_TOMATE
} t_rondelle_type;

// 🍕 Variable globale pour la super rondelle magique
extern char *rondelle; // La rondelle originale, celle qui a tout commencé...

// 🎯 Fonction pour compter les rondelles dans une pizza
int count_rondelles(char *pizza);

// 🔄 Parce qu'une rondelle ça tourne !
void rotate_rondelle(t_rondelle_type *rondelle);

// 🍕 Variable globale pour la rondelle mystérieuse
extern t_rondelle_type la_rondelle_legendaire;

/* 
 * Fun fact: Une rondelle sans trou au milieu,
 * c'est juste un disque qui se la raconte.
 */
# define RONDELLE_MAGIC_NUMBER 42
# define MAX_RONDELLES_PER_PIZZA 1337

int	ft_strlen(char *s);

#endif