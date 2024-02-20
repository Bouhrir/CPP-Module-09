/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:17:35 by obouhrir          #+#    #+#             */
/*   Updated: 2024/01/09 15:43:27 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av){
	if (ac > 1){
		PmergeMe a;
		try{
			a.sort(av, ac);
		}
		catch(std::exception &e){
			cout << e.what() << endl;
		}
	}
	else{
		cout << "Error" << endl;
	}
}