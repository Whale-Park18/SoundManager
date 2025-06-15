#pragma once
#include <QAbstractListModel>
#include <QJsonArray>

#include <vector>

struct AudioPreset
{
	std::string presetName;
	float level;
};

class PresetListModdel : public QAbstractListModel
{
public:
	enum class PresetRole
	{
		Name = Qt::UserRole + 1,
		Level
	};

	// QAbstractListModel��(��) ���� ��ӵ�
	Q_INVOKABLE int rowCount(const QModelIndex& parent) const override;
	Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const override;

	Q_INVOKABLE void addPreset();

private:
	std::vector<AudioPreset> _audioPresetList;
};

