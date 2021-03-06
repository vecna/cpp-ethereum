/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file MiningView.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#pragma once

#include <list>
#include <QtWidgets/QWidget>
#include <libethereum/Client.h>

namespace eth
{
struct MineInfo;
}

class MiningView: public QWidget
{
	Q_OBJECT

public:
	MiningView(QWidget* _p = nullptr);

	void appendStats(std::list<eth::MineInfo> const& _l, eth::MineProgress const& _p);
	void resetStats();

protected:
	virtual void paintEvent(QPaintEvent*);

private:
	eth::MineProgress m_progress;
	unsigned m_duration = 300;
	std::vector<float> m_values;
	std::vector<float> m_bests;
	std::vector<float> m_reqs;
	std::vector<int> m_resets;
	std::vector<int> m_completes;
	double m_lastBest = 1e31;
	bool m_haveReset = false;
};
