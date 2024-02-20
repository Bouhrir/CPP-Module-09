/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:35:23 by obouhrir          #+#    #+#             */
/*   Updated: 2024/01/03 16:35:34 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av){
		
	if (ac == 2){
		try{
			RPN p;
			
			p.rpn(av[1]);
		}
		catch(std::exception &e){
			std::cerr << e.what() << endl;
		}
		
	}
	else
		std::cerr << "to many argv" << endl;
}