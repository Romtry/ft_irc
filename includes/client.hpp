/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:17:58 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/24 14:48:23 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

class client
{
	private:
	
		std::string _nick;
		bool _pass;
		std::string _user;
	public:
		client();
		~client();
};
