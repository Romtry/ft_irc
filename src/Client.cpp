/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:01:32 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/29 12:30:01 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

void Client::sendMessage(const std::string &message) const
{
	send(_clientsSocket, message.c_str(), message.size(), 0);
}
